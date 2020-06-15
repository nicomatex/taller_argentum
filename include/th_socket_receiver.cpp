#include "th_socket_receiver.h"

#include "my_exception.h"
#include "socket_exception.h"

// Temp
#include <iostream>

ThSocketReceiver::ThSocketReceiver(int id, Socket& socket,
                                   BlockingThEventHandler& recieve_handler)
    : Thread(),
      running(false),
      client_id(id),
      protocol(socket),
      recieve_handler(recieve_handler) {}

ThSocketReceiver::ThSocketReceiver(ThSocketReceiver&& other)
    : Thread(std::move(other)),
      protocol(other.protocol),
      recieve_handler(other.recieve_handler) {}

void ThSocketReceiver::run() {
    running = true;
    std::unique_lock<std::mutex> lock(mutex);
    while (running && protocol.get_socket().is_connected()) {
        try {
            Event ev;
            protocol >> ev;
            nlohmann::json json_ev = ev.get_json();
            json_ev["client_id"] = client_id;
            recieve_handler.push_event(Event(json_ev));
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
