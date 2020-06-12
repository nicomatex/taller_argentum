#include "protocol.h"

#include "my_exception.h"
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

Protocol& Protocol::operator<<(const uint32_t num) {
    uint32_t aux = htonl(num);
    socket_ref.get().send((char*)&aux, sizeof(uint32_t));
    return *this;
}
Protocol& Protocol::operator>>(uint32_t& num) {
    uint32_t aux;
    socket_ref.get().recv((char*)&aux, sizeof(uint32_t));
    num = ntohl(aux);
    return *this;
}

Protocol& Protocol::operator<<(const Event& ev) {
    std::vector<uint8_t> v = Translator::serialize(ev);
    if (v.size() > UINT32_MAX)
        throw MyException(
            "The serialized message excedes the uint32 size capacity");
    operator<<((uint32_t)v.size());
    socket_ref.get().send((char*)v.data(), v.size());
    return *this;
}

Protocol& Protocol::operator>>(Event& ev) {
    uint32_t size;
    operator>>(size);
    std::vector<uint8_t> v(size, 0);
    socket_ref.get().recv((char*)v.data(), size);
    ev = Event(Translator::deserialize(v));
    return *this;
}

Protocol::~Protocol() {}
