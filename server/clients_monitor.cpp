#include "clients_monitor.h"

#include "../include/my_exception.h"
#include "../include/socket_exception.h"
#include "event_factory.h"
#include "server_manager.h"
#include "th_dispatcher.h"

// Temp
#include <iostream>

ClientsMonitor::ClientsMonitor() {}

ClientsMonitor::~ClientsMonitor() {}

void ClientsMonitor::add_client(ClientId client_id, SocketManager* client) {
    std::unique_lock<std::mutex> l(m);
    clients[client_id] = client;
    connected_clients.emplace(client_id);
}

SocketManager* ClientsMonitor::rm_client(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (connected_clients.count(client_id)) {
        throw MyException("rm_client: El cliente no se eliminó apropiadamente");
    }
    SocketManager* client = clients.at(client_id);
    clients.erase(client_id);
    return client;
}

void ClientsMonitor::send_to(ClientId client_id, Event ev) {
    std::unique_lock<std::mutex> l(m);
    try {
        if (connected_clients.count(client_id))
            clients[client_id]->send(ev);
    } catch (const ConnectionClosedSocketException& e) {
        drop(client_id);
    }
}

void ClientsMonitor::drop(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (!connected_clients.count(client_id))
        return;
    connected_clients.erase(client_id);
    ServerManager::get_instance().get_dispatcher().push_event(
        EventFactory::drop_client(client_id));
}

void ClientsMonitor::drop_all() {
    std::unique_lock<std::mutex> l(m);
    for (auto it = connected_clients.begin(); it != connected_clients.end();) {
        std::cerr << "ClientsMonitor: dropping " << *it << std::endl;
        ServerManager::get_instance().get_dispatcher().push_event(
            EventFactory::drop_client(*it));
        it = connected_clients.erase(it);
    }
}
