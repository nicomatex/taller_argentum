#include "session.h"

#include "../include/blocking_th_event_handler.h"

// Temp
#include <iostream>

Session::Session(Map& map) : broadcaster(clients), observer(map, broadcaster) {}

void Session::start() {
    broadcaster.start();
}

void Session::stop() {
    broadcaster.stop();
}

void Session::join() {
    broadcaster.join();
}

void Session::add_client(int new_client) {
    clients.add_client(new_client);
}

void Session::rm_client(int id) {
    clients.rm_client(id);
}

Session::~Session() {}
