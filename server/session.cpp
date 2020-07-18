#include "session.h"

#include "../include/blocking_th_event_handler.h"

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
    clients.add_client(new_client, entity_id);
}

EntityId Session::rm_client(ClientId client_id) {
    EntityId player_id = clients.at(client_id);
    clients.rm_client(client_id);
    return player_id;
}

MapMonitor& Session::get_map() {
    return map;
}

void Session::push_action(ClientId client_id, Action* action) {
    if (!clients.count(client_id))
        return;
    map.push_action(clients.at(client_id), action);
}

void Session::broadcast(const Event& ev) {
    broadcaster.push_event(ev);
}

Session::~Session() {}
