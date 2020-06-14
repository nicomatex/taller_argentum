#include "th_socket_receiver.h"

#include "my_exception.h"
#include "socket_exception.h"

// Temp
#include <iostream>

ThSocketReceiver::ThSocketReceiver(Socket& socket,
                                   BlockingThEventHandler* recieve_handler)
    : Thread(),
      running(false),
      protocol(socket),
      recieve_handler(recieve_handler) {}

ThSocketReceiver::ThSocketReceiver(ThSocketReceiver&& other)
    : Thread(std::move(other)),
      protocol(other.protocol),
      recieve_handler(other.recieve_handler) {}
ThSocketReceiver& ThSocketReceiver::operator=(ThSocketReceiver&& other) {
    Thread::operator=(std::move(other));
    protocol = Protocol(other.protocol);
    recieve_handler = other.recieve_handler;
    return *this;
}

void ThSocketReceiver::assign_handler(BlockingThEventHandler* new_handler) {
    std::unique_lock<std::mutex> lock(mutex);
    recieve_handler = new_handler;
    cond_var.notify_all();
}

void ThSocketReceiver::run() {
    running = true;
    std::unique_lock<std::mutex> lock(mutex);
    while (running && protocol.get_socket().is_connected()) {
        if (!lock.owns_lock())
            lock.lock();
        while (running && !recieve_handler) {
            // Permite que ocurra la reasociación del handler
            cond_var.wait(lock);
        }
        if (!running)
            break;
        try {
            Event ev;
            protocol >> ev;
            recieve_handler->push_event(ev);
            lock.unlock();
        } catch (const ConnectionClosedSocketException& e) {
            running = false;
        } catch (const EventHandlerStoppedException& e) {
            running = false;
        }
    }
}

void ThSocketReceiver::stop() {
    running = false;
    cond_var.notify_all();
}

ThSocketReceiver::~ThSocketReceiver() {}
