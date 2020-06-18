#include "th_socket_sender.h"

#include "socket_exception.h"

// Temp
#include <iostream>

void ThSocketSender::handle(Event& ev) {
    try {
        protocol << ev;
    } catch (const ConnectionClosedSocketException& e) {
        stop();
    }
}

ThSocketSender::ThSocketSender(Socket& socket)
    : BlockingThEventHandler(), protocol(socket) {}

ThSocketSender::ThSocketSender(ThSocketSender&& other)
    : BlockingThEventHandler(std::move(other)), protocol(other.protocol) {}
ThSocketSender& ThSocketSender::operator=(ThSocketSender&& other) {
    BlockingThEventHandler::operator=(std::move(other));
    protocol = other.protocol;
    return *this;
}

ThSocketSender::~ThSocketSender() {}
