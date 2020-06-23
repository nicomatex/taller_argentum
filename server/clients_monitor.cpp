#include "clients_monitor.h"

ClientsMonitor::ClientsMonitor() {}

ClientsMonitor::~ClientsMonitor() {}

void ClientsMonitor::add_client(ClientId client_id, SocketManager* client) {
    std::unique_lock<std::mutex> l(m);
    clients[client_id] = client;
}

SocketManager* ClientsMonitor::rm_client(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    SocketManager* client = clients.at(client_id);
    clients.erase(client_id);
    return client;
}

void ClientsMonitor::send_to(ClientId client_id, Event ev) {
    std::unique_lock<std::mutex> l(m);
    clients[client_id]->send(ev);
}
