#include "th_broadcaster.h"

// Temp
#include <iostream>

void ThBroadcaster::handle(Event& ev) {
    std::cerr << "Broadcaster: Broadcasting: " << ev.str << std::endl;
    clients.broadcast(ev);
}

ThBroadcaster::ThBroadcaster(ClientsMonitor& clients)
    : ThEventHandler(), clients(clients) {}

ThBroadcaster::~ThBroadcaster() {}
