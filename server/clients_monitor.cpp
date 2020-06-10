#include "clients_monitor.h"

// Temp
#include <iostream>

ClientsMonitor::ClientsMonitor() {}

void ClientsMonitor::add_client(SocketManager* new_client) {
    std::unique_lock<std::mutex> lock(mutex);
    if (clients.count(new_client->get_id()))
        return;
    clients[new_client->get_id()] = new_client;
}

SocketManager* ClientsMonitor::rm_client(int id) {
    std::unique_lock<std::mutex> lock(mutex);
    if (!clients.count(id))
        return NULL;
    SocketManager* deleted = clients[id];
    clients.erase(id);
    return deleted;
}

void ClientsMonitor::send_to(size_t id, const Command& ev) {
    std::unique_lock<std::mutex> lock(mutex);
    try {
        clients[id]->send(ev);
    } catch (const EventHandlerStoppedException& e) {
        clients.erase(id);
    }
}

void ClientsMonitor::broadcast(Command& ev) {
    std::unique_lock<std::mutex> lock(mutex);
    for (auto it = clients.begin(); it != clients.end();) {
        try {
            it->second->send(ev);
            it++;
        } catch (const EventHandlerStoppedException& e) {
            it = clients.erase(it);
        }
    }
}

void ClientsMonitor::join_finished(bool wait) {
    std::unique_lock<std::mutex> lock(mutex);
    for (auto it = clients.begin(); it != clients.end();) {
        SocketManager* client = it->second;
        if (!wait && !client->is_done()) {
            it++;
            continue;
        }
        client->stop(false);
        client->join();
        it = clients.erase(it);
        delete client;
    }
}

ClientsMonitor::~ClientsMonitor() {}
