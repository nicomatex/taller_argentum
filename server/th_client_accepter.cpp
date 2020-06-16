#include "th_client_accepter.h"

#include <iostream>
#include <utility>

#include "../include/my_exception.h"
#include "../include/socket_exception.h"
#include "../include/socket_manager.h"
#include "server_manager.h"

ThClientAccepter::ThClientAccepter(Socket listener)
    : Thread(), listener(std::move(listener)), running(true), next_free_id(0) {}

void ThClientAccepter::run() {
    try {
        ServerManager& server_manager = ServerManager::get_instance();
        while (running && listener.is_open()) {
            try {
                SocketManager* new_client =
                    new SocketManager(next_free_id, listener.accept(),
                                      server_manager.get_dispatcher());
                std::cerr << "Accepter: Started client: " << next_free_id
                          << std::endl;
                new_client->start();
                server_manager.add_client(next_free_id, new_client);
                next_free_id++;
            } catch (const ConnectionClosedSocketException& e) {
                running = false;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ThClientAccepter::stop() {
    running = false;
    listener.shutdown_and_close();
}

ThClientAccepter::~ThClientAccepter() {}
