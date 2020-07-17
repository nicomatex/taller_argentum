#include "clients_names_monitor.h"

#include "server_exceptions.h"

ClientsNamesMonitor::ClientsNamesMonitor() {}
ClientsNamesMonitor::~ClientsNamesMonitor() {}

void ClientsNamesMonitor::add_name(ClientId client_id,
                                   const std::string& name) {
    std::unique_lock<std::mutex> l(m);
    if (clients_names.second.count(name) &&
        client_id != clients_names.second.at(name))
        throw DuplicatedPlayerException(name);
    clients_names.first.emplace(client_id, name);
    clients_names.second.emplace(name, client_id);
}

void ClientsNamesMonitor::rm_name(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (!clients_names.first.count(client_id))
        // Este caso sirve si un jugador nunca mandó el mensaje de
        // inicialización
        return;
    std::string name = clients_names.first.at(client_id);
    clients_names.first.erase(client_id);
    clients_names.second.erase(name);
}

ClientId ClientsNamesMonitor::get_client(const std::string& name) {
    std::unique_lock<std::mutex> l(m);
    if (!clients_names.second.count(name))
        throw ClientDisconnectedException(name);
    return clients_names.second.at(name);
}

const std::string& ClientsNamesMonitor::get_name(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    if (!clients_names.first.count(client_id))
        throw ClientDisconnectedException(client_id);
    return clients_names.first.at(client_id);
}
