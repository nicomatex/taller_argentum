#include "th_socket_receiver.h"

#include "../my_exception.h"
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
    try {
        running = true;
        while (running && protocol.get_socket().is_connected()) {
            Event ev;
            try {
                protocol >> ev;
                nlohmann::json json_ev = ev.get_json();
                json_ev["client_id"] = client_id;
                recieve_handler.push_event(Event(json_ev));
            } catch (const nlohmann::detail::exception& e) {
                std::cerr << "SocketReceiver: error in json: " << ev.get_json()
                          << std::endl;
                continue;
            } catch (const ConnectionClosedSocketException& e) {
                running = false;
            } catch (const EventHandlerStoppedException& e) {
                running = false;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "SocketRecvHandler: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "SocketRecvHandler: Unknown exception" << std::endl;
    }
}

void ThSocketReceiver::stop() {
    running = false;
}

ThSocketReceiver::~ThSocketReceiver() {}
