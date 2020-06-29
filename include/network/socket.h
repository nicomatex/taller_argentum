#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "../my_exception.h"

class Socket {
   private:
    bool _is_open;
    bool _is_connected;
    int socketfd;

    // Private from fd
    explicit Socket(int socketfd);

    int get_results(struct addrinfo** results, const char* node,
                    const char* service, int flags);

    int get_socketfd(struct addrinfo* results,
                     int (*setup)(int, const struct sockaddr*, socklen_t));

    int socket_setup(const char* node, const char* port,
                     int (*setup)(int, const struct sockaddr*, socklen_t),
                     int flags);

   public:
    // Client
    Socket(const std::string& node, const std::string& port);

    // Server
    Socket(const std::string& port, const size_t& max_client_q);

    // Cannot be copied
    Socket(const Socket& other) = delete;
    Socket& operator=(Socket& other) = delete;

    // Move Constructor
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    // If socket was created for host-side, accept a client as a Socket
    Socket accept();

    bool is_connected() const;

    bool is_open() const;

    // Send lenght ammount of bytes
    size_t send(const char* bytes, size_t lenght);

    // Send a char
    Socket& operator<<(const char c);

    // Recieve at most size ammout of bytes
    size_t recv(char* buffer, size_t size);

    // Recieve a char
    Socket& operator>>(char& c);

    void shutdown_and_close();

    ~Socket();
};

#endif  //__SOCKET_H__
