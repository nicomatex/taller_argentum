#define _POSIX_C_SOURCE 200112L

#include "socket.h"

#include <memory.h>

#include <utility>

#include "my_exception.h"
#include "socket_exception.h"

#define SOCKETFD_ERROR -1
#define SENT_ERROR -1
#define RECV_ERROR -1
#define CONECTION_CLOSED 0

/*****************************************************************************/
// Funciones auxiliares

static void _initialize_hints(struct addrinfo* hints, int family, int socktype,
                              int flags, int protocol) {
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = family;
    hints->ai_socktype = socktype;
    hints->ai_flags = flags;
    hints->ai_protocol = protocol;
}

static int _bind(int skt, const struct sockaddr* addr, socklen_t len) {
    int aux = 1;
    if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &aux, sizeof(aux)) ==
        SOCKETFD_ERROR)
        return SOCKETFD_ERROR;

    return bind(skt, addr, len);
}

static int _accept(int fd, sockaddr* addr, socklen_t* addr_len) {
    return accept(fd, addr, addr_len);
}

static int _send(int sktfd, const void* bytes, size_t lenght) {
    return send(sktfd, bytes, lenght, MSG_NOSIGNAL);
}

static int _recv(int sktfd, void* buffer, size_t size) {
    return recv(sktfd, buffer, size, 0);
}

/*****************************************************************************/

int Socket::get_results(struct addrinfo** results, const char* node,
                        const char* service, int flags) {
    struct addrinfo hints;
    _initialize_hints(&hints, AF_INET, SOCK_STREAM, flags, 0);
    return getaddrinfo(node, service, &hints, results);
}

int Socket::get_socketfd(struct addrinfo* results,
                         int (*setup)(int, const struct sockaddr*, socklen_t)) {
    struct addrinfo* current;
    int socketfd;
    int aux;

    for (current = results; current != NULL; current = current->ai_next) {
        socketfd = socket(current->ai_family, current->ai_socktype,
                          current->ai_protocol);
        if (socketfd == SOCKETFD_ERROR)
            // No hay conexión para este resultado
            continue;
        aux = setup(socketfd, current->ai_addr, current->ai_addrlen);
        if (aux == EXIT_SUCCESS)
            break;
        close(socketfd);
    }
    if (current == NULL)
        return SOCKETFD_ERROR;

    return socketfd;
}

int Socket::socket_setup(const char* node, const char* port,
                         int (*setup)(int, const struct sockaddr*, socklen_t),
                         int flags) {
    struct addrinfo* results;
    int return_code;

    return_code = get_results(&results, node, port, flags);
    if (return_code != EXIT_SUCCESS)
        return return_code;

    return_code = get_socketfd(results, setup);
    freeaddrinfo(results);
    return return_code;
}

Socket::Socket(int socketfd)
    : _is_open(false), _is_connected(true), socketfd(socketfd) {}

Socket::Socket(const std::string& node, const std::string& port)
    : _is_open(false), _is_connected(false) {
    socketfd = socket_setup(node.c_str(), port.c_str(), connect, 0);
    if (socketfd < 0)
        throw MyException("Socket: No se pudo abrir el socket indicado: %s %s",
                          node.c_str(), port.c_str());
    _is_connected = true;
}

Socket::Socket(const std::string& port, const size_t& max_client_q)
    : _is_open(false), _is_connected(false) {
    // BIND
    socketfd = socket_setup(NULL, port.c_str(), _bind, AI_PASSIVE);
    if (socketfd < 0)
        throw MyException("Error in Socket Bind");
    // LISTEN
    if (listen(socketfd, max_client_q))
        throw MyException("Error in Socket Listen");
    _is_open = true;
}

Socket::Socket(Socket&& other) {
    _is_open = other._is_open;
    _is_connected = other._is_connected;
    socketfd = other.socketfd;
    other._is_open = false;
    other._is_connected = false;
    other.socketfd = SOCKETFD_ERROR;
}

Socket& Socket::operator=(Socket&& other) {
    if (this == &other)
        return *this;
    shutdown_and_close();
    _is_open = other._is_open;
    _is_connected = other._is_connected;
    socketfd = other.socketfd;
    other._is_open = false;
    other._is_connected = false;
    other.socketfd = SOCKETFD_ERROR;
    return *this;
}

Socket Socket::accept() {
    if (!_is_open)
        throw ConnectionClosedSocketException();
    int peer = _accept(socketfd, NULL, NULL);
    if (peer == SOCKETFD_ERROR)
        throw ConnectionClosedSocketException();
    return std::move(Socket(peer));
}

bool Socket::is_connected() const {
    return _is_connected;
}

bool Socket::is_open() const {
    return _is_open;
}

size_t Socket::send(const char* bytes, size_t lenght) {
    if (!_is_connected)
        throw ConnectionClosedSocketException();
    size_t sent = 0;
    int count = 0;

    while (sent < lenght && _is_connected) {
        count = _send(socketfd, &bytes[sent], lenght - sent);
        if (count == SENT_ERROR) {
            throw MyException("Error in Socket Send");
        } else if (count == CONECTION_CLOSED) {
            _is_connected = false;
            throw ConnectionClosedSocketException();
        } else {
            sent += count;
        }
    }
    return sent;
}

Socket& Socket::operator<<(const char c) {
    send(&c, sizeof(char));
    return *this;
}

size_t Socket::recv(char* buffer, size_t size) {
    if (!_is_connected)
        throw ConnectionClosedSocketException();
    size_t read = 0;
    int count = 0;

    while (read < size && _is_connected) {
        count = _recv(socketfd, &buffer[read], size - read);
        if (count == RECV_ERROR) {
            throw MyException("Error in Socket Recieve");
        } else if (count == CONECTION_CLOSED) {
            _is_connected = false;
            throw ConnectionClosedSocketException();
        } else {
            read += count;
        }
    }
    return read;
}

Socket& Socket::operator>>(char& c) {
    recv(&c, sizeof(char));
    return *this;
}

void Socket::shutdown_and_close() {
    if (_is_connected || _is_open) {
        shutdown(socketfd, SHUT_RDWR);
        close(socketfd);
    }
    socketfd = SOCKETFD_ERROR;
    _is_open = false;
    _is_connected = false;
}

Socket::~Socket() {
    shutdown_and_close();
}
