#include "th_socket_sender.h"

#include "socket_exception.h"

// Temp
#include <iostream>

void ThSocketSender::handle(Command& ev) {
    try {
        protocol << ev;
    } catch (const ConnectionClosedSocketException& e) {
        stop();
    }
}

ThSocketSender::ThSocketSender(Socket& socket)
    : ThEventHandler(), protocol(socket) {}

ThSocketSender::ThSocketSender(ThSocketSender&& other)
    : ThEventHandler(std::move(other)), protocol(other.protocol) {}
ThSocketSender& ThSocketSender::operator=(ThSocketSender&& other) {
    ThEventHandler::operator=(std::move(other));
    protocol = other.protocol;
    return *this;
}

ThSocketSender::~ThSocketSender() {}
