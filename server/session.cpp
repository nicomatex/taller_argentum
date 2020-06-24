#include "session.h"

#include "../include/blocking_th_event_handler.h"

// Temp
#include <iostream>

Session::Session(MapMonitor& map)
    : broadcaster(clients), observer(map, broadcaster) {}

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
    observer.refresh_entities();
    clients.add_client(new_client);
}

void Session::rm_client(ClientId id) {
    observer.refresh_entities();
    clients.rm_client(id);
}

void Session::broadcast(const Event& ev) {
    broadcaster.push_event(ev);
}

Session::~Session() {}
