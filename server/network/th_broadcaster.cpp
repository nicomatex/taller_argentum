#include "th_broadcaster.h"

// Temp
#include <iostream>

void ThBroadcaster::handle(Event& ev) {
    try {
        clients.broadcast(ev);
    } catch (const nlohmann::detail::exception& e) {
        std::cerr << "Broadcaster: error in json: " << ev.get_json()
                  << std::endl;
    }
}

ThBroadcaster::ThBroadcaster(ClientIdSet& clients)
    : BlockingThEventHandler(), clients(clients) {}

ThBroadcaster::~ThBroadcaster() {}
