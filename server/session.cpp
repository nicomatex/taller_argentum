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

void Session::stop() {
    broadcaster.stop();
    observer.stop();
}

void Session::join() {
    broadcaster.join();
    observer.join();
}

void Session::add_client(ClientId new_client) {
    clients.add_client(new_client);
}

void Session::rm_client(ClientId id) {
    clients.rm_client(id);
}

MapMonitor& Session::get_map() {
    return map;
}

void Session::broadcast(const Event& ev) {
    broadcaster.push_event(ev);
}

Session::~Session() {}
