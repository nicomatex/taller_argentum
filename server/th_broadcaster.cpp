#include "th_broadcaster.h"

// Temp
#include <iostream>

void ThBroadcaster::handle(Event& ev) {
    std::cerr << "Broadcaster: Broadcasting: " << ev.get_json().dump()
              << std::endl;
    clients.broadcast(ev);
}

ThBroadcaster::ThBroadcaster(ClientsMonitor& clients)
    : BlockingThEventHandler(), clients(clients) {}

ThBroadcaster::~ThBroadcaster() {}
