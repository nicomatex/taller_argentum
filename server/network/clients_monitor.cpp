#include "clients_monitor.h"

#include "../../include/my_exception.h"
#include "../../include/network/socket_exception.h"
#include "../events/event_factory.h"
#include "../server_manager.h"
#include "../th_dispatcher.h"

// Temp
#include <iostream>

ClientsMonitor::ClientsMonitor() {}

ClientsMonitor::~ClientsMonitor() {}

void ClientsMonitor::add_client(ClientId client_id, SocketManager* client) {
    std::unique_lock<std::recursive_mutex> l(m);
    clients[client_id] = client;
    connected_clients.emplace(client_id);
}

SocketManager* ClientsMonitor::rm_client(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    if (connected_clients.count(client_id)) {
        connected_clients.erase(client_id);
        std::cerr << "ClientsMonitor: El cliente : " << client_id
                  << " fue eliminado de forma repentina." << std::endl;
        return nullptr;
    }
    SocketManager* client = clients.at(client_id);
    clients.erase(client_id);
    return client;
}

void ClientsMonitor::send_to(ClientId client_id, Event ev) {
    std::unique_lock<std::recursive_mutex> l(m);
    try {
        if (connected_clients.count(client_id))
            clients[client_id]->send(ev);
    } catch (const ConnectionClosedSocketException& e) {
        drop(client_id);
    }
}

void ClientsMonitor::drop(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    if (!connected_clients.count(client_id))
        return;
    connected_clients.erase(client_id);
    ServerManager::get_instance().get_dispatcher().push_event(
        EventFactory::drop_client(client_id));
}

void ClientsMonitor::drop_all() {
    std::unique_lock<std::recursive_mutex> l(m);
    std::cerr << "ClientsMonitor: dropping all clients" << std::endl;
    for (auto it = connected_clients.begin(); it != connected_clients.end();) {
        try {
            clients[*it]->send(EventFactory::disconnect());
        } catch (const ConnectionClosedSocketException& e) {
        }
        ServerManager::get_instance().get_dispatcher().push_event(
            EventFactory::drop_client(*it));
        it = connected_clients.erase(it);
    }
}
