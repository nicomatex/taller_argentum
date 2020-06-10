#include "th_client_accepter.h"

#include <iostream>
#include <utility>

#include "../include/socket_exception.h"
#include "../include/socket_manager.h"

ThClientAccepter::ThClientAccepter(Socket listener)
    : Thread(), listener(std::move(listener)), running(true), next_free_id(0) {}

void ThClientAccepter::run() {
    session.start();
    while (running && listener.is_open()) {
        try {
            SocketManager* new_client =
                new SocketManager(next_free_id, listener.accept());
            new_client->start();
            std::cerr << "Accepter: Started client: " << next_free_id
                      << std::endl;
            session.add_client(new_client);
            next_free_id++;
            session.join_finished(false);
        } catch (const ConnectionClosedSocketException& e) {
            running = false;
        }
    }
    session.join_finished(true);
    session.stop();
    session.join();
    std::cerr << "Session finished" << std::endl;
}

void ThClientAccepter::stop() {
    running = false;
    listener.shutdown_and_close();
}

ThClientAccepter::~ThClientAccepter() {}
