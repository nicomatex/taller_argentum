#include "socket_exception.h"

ConnectionClosedSocketException::ConnectionClosedSocketException() {
    error = "Socket encountered a Connection Closed error";
}

const char* ConnectionClosedSocketException::what() const noexcept {
    return error.c_str();
}

ConnectionClosedSocketException::~ConnectionClosedSocketException() {}
