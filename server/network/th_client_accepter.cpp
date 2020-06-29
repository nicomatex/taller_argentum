#include "th_client_accepter.h"

#include <iostream>
#include <utility>

#include "../../include/my_exception.h"
#include "../../include/network/socket_exception.h"
#include "../../include/network/socket_manager.h"
#include "../server_manager.h"

ThClientAccepter::ThClientAccepter(Socket listener)
    : Thread(), listener(std::move(listener)), running(true) {}

ClientId ThClientAccepter::get_next_id() {
    static ClientId next_free_id = 0;
    return next_free_id++;
}

void ThClientAccepter::run() {
    try {
        ServerManager& server_manager = ServerManager::get_instance();
        while (running && listener.is_open()) {
            try {
                ClientId id = get_next_id();
                SocketManager* new_client = new SocketManager(
                    id, listener.accept(), server_manager.get_dispatcher());
                std::cerr << "Accepter: Started client: " << id << std::endl;
                new_client->start();
                server_manager.add_client(id, new_client);
            } catch (const ConnectionClosedSocketException& e) {
                running = false;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "ClientAccepter: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ClientAccepter: Unknown Exception" << std::endl;
    }
}

void ThClientAccepter::stop() {
    running = false;
    listener.shutdown_and_close();
}

ThClientAccepter::~ThClientAccepter() {}
