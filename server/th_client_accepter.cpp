#include "th_client_accepter.h"

#include <iostream>
#include <utility>

#include "../include/socket_exception.h"
#include "../include/socket_manager.h"

ThClientAccepter::ThClientAccepter(Socket listener,
                                   SessionManager& session_manager)
    : Thread(),
      listener(std::move(listener)),
      running(true),
      next_free_id(0),
      session_manager(session_manager) {}

void ThClientAccepter::run() {
    while (running && listener.is_open()) {
        try {
            SocketManager* new_client =
                new SocketManager(next_free_id, listener.accept());
            new_client->start();
            std::cerr << "Accepter: Started client: " << next_free_id
                      << std::endl;
            session_manager.add_client(new_client);
            next_free_id++;
        } catch (const ConnectionClosedSocketException& e) {
            throw MyException("\tAccepter: Listener closed unexpectedly");
            running = false;
        }
    }
    if (!listener.is_open())
        throw MyException("\tAccepter: Listener closed unexpectedly");
    listener.shutdown_and_close();
    std::cerr << "\tAccepter: finished" << std::endl;
}

void ThClientAccepter::stop() {
    running = false;
}

ThClientAccepter::~ThClientAccepter() {}
