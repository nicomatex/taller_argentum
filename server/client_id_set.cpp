#include "client_id_set.h"

#include "server_manager.h"

// Temp
#include <iostream>

ClientIdSet::ClientIdSet() {}

void ClientIdSet::add_client(int client_id) {
    std::unique_lock<std::mutex> lock(mutex);
    if (clients.count(client_id))
        return;
    clients.emplace(client_id);
}

void ClientIdSet::rm_client(int id) {
    std::unique_lock<std::mutex> lock(mutex);
    if (!clients.count(id))
        return;
    clients.erase(id);
}

void ClientIdSet::send_to(int id, const Event& ev) {
    std::unique_lock<std::mutex> lock(mutex);
    ServerManager& server_manager = ServerManager::get_instance();
    try {
        if (clients.count(id))
            server_manager.send_to(id, ev);
    } catch (const EventHandlerStoppedException& e) {
        clients.erase(id);
    }
}

void ClientIdSet::broadcast(Event& ev) {
    std::unique_lock<std::mutex> lock(mutex);
    ServerManager& server_manager = ServerManager::get_instance();
    for (auto it = clients.begin(); it != clients.end();) {
        // try {
        server_manager.send_to(*it, ev);
        it++;
        // } catch (const ClientDisconnectedException& e) {
        //     it = clients.erase(it);
        // }
    }
}

ClientIdSet::~ClientIdSet() {}
