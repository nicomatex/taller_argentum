#include "th_broadcaster.h"

// Temp
#include <iostream>

void ThBroadcaster::handle(Event& ev) {
    clients.broadcast(ev);
}

ThBroadcaster::ThBroadcaster(ClientIdSet& clients)
    : BlockingThEventHandler(), clients(clients) {}

ThBroadcaster::~ThBroadcaster() {}
