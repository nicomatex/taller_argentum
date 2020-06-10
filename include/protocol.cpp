#include "protocol.h"

#include "translator.h"

Protocol::Protocol(Socket& socket) : socket_ref(socket) {}

Protocol::Protocol(const Protocol& other)
    : socket_ref(other.socket_ref.get()) {}

Protocol& Protocol::operator=(const Protocol& other) {
    socket_ref = other.socket_ref;
    return *this;
}

const Socket& Protocol::get_socket() {
    return socket_ref.get();
}

Protocol& Protocol::operator<<(const char c) {
    socket_ref.get() << c;
    return *this;
}
Protocol& Protocol::operator>>(char& c) {
    socket_ref.get() >> c;
    return *this;
}

Protocol& Protocol::operator<<(const std::string& str) {
    operator<<((uint32_t)str.size());
    std::vector<char> a_enviar = Traductor::serializar(str);
    socket_ref.get().send(a_enviar.data(), a_enviar.size());
    return *this;
}
Protocol& Protocol::operator>>(std::string& str) {
    uint32_t tamanio;
    operator>>(tamanio);
    std::vector<char> recibido(tamanio, 0);
    socket_ref.get().recv(recibido.data(), tamanio);
    str = Traductor::deserializar(recibido);
    return *this;
}

Protocol& Protocol::operator<<(const uint16_t num) {
    uint16_t aux = htons(num);
    socket_ref.get().send((char*)&aux, sizeof(uint16_t));
    return *this;
}
Protocol& Protocol::operator<<(const uint32_t num) {
    uint32_t aux = htonl(num);
    socket_ref.get().send((char*)&aux, sizeof(uint32_t));
    return *this;
}
Protocol& Protocol::operator>>(uint16_t& num) {
    uint16_t aux;
    socket_ref.get().recv((char*)&aux, sizeof(uint16_t));
    num = ntohs(aux);
    return *this;
}
Protocol& Protocol::operator>>(uint32_t& num) {
    uint32_t aux;
    socket_ref.get().recv((char*)&aux, sizeof(uint32_t));
    num = ntohl(aux);
    return *this;
}

Protocol& Protocol::operator<<(const Command& ev) {
    operator<<(ev.str);
    return *this;
}

Protocol& Protocol::operator>>(Command& ev) {
    operator>>(ev.str);
    return *this;
}

Protocol::~Protocol() {}
