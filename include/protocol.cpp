#include "protocol.h"

#include "translator.h"

Protocol::Protocol(Socket& socket) : socket(socket) {}

Protocol& Protocol::operator<<(const char c) {
    socket << c;
    return *this;
}
Protocol& Protocol::operator>>(char& c) {
    socket >> c;
    return *this;
}

Protocol& Protocol::operator<<(const std::string& str) {
    operator<<((uint32_t)str.size());
    std::vector<char> a_enviar = Traductor::serializar(str);
    socket.send(a_enviar.data(), a_enviar.size());
    return *this;
}
Protocol& Protocol::operator>>(std::string& str) {
    uint32_t tamanio;
    operator>>(tamanio);
    std::vector<char> recibido(tamanio, 0);
    socket.recv(recibido.data(), tamanio);
    str = Traductor::deserializar(recibido);
    return *this;
}

Protocol& Protocol::operator<<(const uint16_t num) {
    uint16_t aux = htons(num);
    socket.send((char*)&aux, sizeof(uint16_t));
    return *this;
}
Protocol& Protocol::operator<<(const uint32_t num) {
    uint32_t aux = htonl(num);
    socket.send((char*)&aux, sizeof(uint32_t));
    return *this;
}
Protocol& Protocol::operator>>(uint16_t& num) {
    uint16_t aux;
    socket.recv((char*)&aux, sizeof(uint16_t));
    num = ntohs(aux);
    return *this;
}
Protocol& Protocol::operator>>(uint32_t& num) {
    uint32_t aux;
    socket.recv((char*)&aux, sizeof(uint32_t));
    num = ntohl(aux);
    return *this;
}

Protocol::~Protocol() {}
