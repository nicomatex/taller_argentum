#include "th_client_accepter.h"

#include <iostream>
#include <utility>

#include "../include/my_exception.h"
#include "../include/socket_exception.h"
#include "../include/socket_manager.h"

ThClientAccepter::ThClientAccepter(Socket listener,
                                   ServerManager& server_manager)
    : Thread(),
      listener(std::move(listener)),
      running(true),
      next_free_id(0),
      server_manager(server_manager) {}

void ThClientAccepter::run() {
    while (running && listener.is_open()) {
        try {
            SocketManager* new_client =
                new SocketManager(next_free_id, listener.accept());
            std::cerr << "Accepter: Started client: " << next_free_id
                      << std::endl;
            new_client->start();
            server_manager.add_client(new_client);
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
