#include "client_id_set.h"

#include "../server_manager.h"

// Temp
#include <iostream>

ClientToEntityMap::ClientToEntityMap() {}

void ClientToEntityMap::add_client(ClientId client_id, EntityId entity_id) {
    std::unique_lock<std::mutex> l(m);
    if (client_to_entity.count(client_id))
        return;
    client_to_entity.emplace(client_id, entity_id);
}

void ClientToEntityMap::rm_client(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (!client_to_entity.count(client_id))
        return;
    client_to_entity.erase(client_id);
}

bool ClientToEntityMap::count(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    return client_to_entity.count(client_id);
}

EntityId ClientToEntityMap::at(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (!client_to_entity.count(client_id))
        throw ClientDisconnectedException(client_id);
    return client_to_entity.at(client_id);
}

void ClientToEntityMap::send_to(ClientId client_id, const Event& ev) {
    std::unique_lock<std::mutex> l(m);
    if (!client_to_entity.count(client_id))
        return;  // Check
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.send_to(client_id, ev);
}

void ClientToEntityMap::broadcast(Event& ev) {
    std::unique_lock<std::mutex> l(m);
    ServerManager& server_manager = ServerManager::get_instance();
    for (auto it = client_to_entity.begin(); it != client_to_entity.end();
         it++) {
        server_manager.send_to(it->first, ev);
    }
}

ClientToEntityMap::~ClientToEntityMap() {}
