#include "session.h"

#include "../include/blocking_th_event_handler.h"

// Temp
#include <iostream>

Session::Session(MapMonitor& map)
    : map(map), broadcaster(clients), observer(map, broadcaster) {}

void Session::start() {
    broadcaster.start();
    observer.start();
}

void Session::finish() {
    broadcaster.stop();
    observer.stop();
    broadcaster.join();
    observer.join();
}

void Session::add_client(ClientId new_client, EntityId entity_id) {
    std::unique_lock<std::mutex> l(m);
    client_map[new_client] = entity_id;
    clients.add_client(new_client);
}

EntityId Session::rm_client(ClientId client_id) {
    std::unique_lock<std::mutex> l(m);
    EntityId player_id = client_map.at(client_id);
    client_map.erase(client_id);
    clients.rm_client(client_id);
    return player_id;
}

MapMonitor& Session::get_map() {
    return map;
}

void Session::push_action(ClientId client_id, Action* action) {
    std::unique_lock<std::mutex> l(m);
    map.push_action(client_map.at(client_id), action);
}

void Session::broadcast(const Event& ev) {
    broadcaster.push_event(ev);
}

Session::~Session() {}
