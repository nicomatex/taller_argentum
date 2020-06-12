#include "th_socket_receiver.h"

#include "my_exception.h"
#include "socket_exception.h"

ThSocketReceiver::ThSocketReceiver(Socket& socket,
                                   ThEventHandler* recieve_handler)
    : Thread(), protocol(socket), recieve_handler(recieve_handler) {}

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

void ThSocketReceiver::assign_handler(ThEventHandler* new_handler) {
    std::unique_lock<std::mutex> lock(mutex);
    recieve_handler = new_handler;
    cond_var.notify_all();
}

void ThSocketReceiver::run() {
    std::unique_lock<std::mutex> lock(mutex);
    while (protocol.get_socket().is_connected()) {
        if (!lock.owns_lock())
            lock.lock();
        while (!recieve_handler) {
            // Permite que ocurra la reasociación
            cond_var.wait(lock);
        }
        try {
            Event ev;
            protocol >> ev;
            recieve_handler->push_event(ev);
            lock.unlock();
        } catch (const ConnectionClosedSocketException& e) {
            break;
        } catch (const EventHandlerStoppedException& e) {
            break;
        }
    }
}

ThSocketReceiver::~ThSocketReceiver() {}
