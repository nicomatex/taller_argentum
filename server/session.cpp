#include "session.h"

#include "../include/blocking_th_event_handler.h"

// Temp
#include <iostream>

Session::Session(Map& map, BlockingQueue<Event>& queue)
    : broadcaster(clients), dispatcher(queue), observer(map, broadcaster) {}

void Session::start() {
    broadcaster.start();
    dispatcher.start();
}

void Session::stop() {
    dispatcher.stop();
    broadcaster.stop();
}

void Session::join() {
    broadcaster.join();
    dispatcher.join();
}

void Session::add_client(SocketManager* new_client) {
    new_client->assign_handler(
        static_cast<BlockingThEventHandler*>(&dispatcher));
    clients.add_client(new_client);
}

SocketManager* Session::rm_client(int id) {
    SocketManager* removed = clients.rm_client(id);
    removed->assign_handler(nullptr);
    return removed;
}

void Session::join_finished(bool wait) {
    clients.join_finished(wait);
}

Session::~Session() {}
