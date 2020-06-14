#include "th_dispatcher.h"

#include "../nlohmann/json.hpp"
#include "client_initializer.h"
#include "server_manager.h"
#include "th_event_handler.h"

// Temp
#include <iostream>

ThDispatcherHandler::ThDispatcherHandler() {}

void ThDispatcherHandler::handle(Event& ev) {
    nlohmann::json json_ev = ev.get_json();
    switch (int(json_ev["ev_id"])) {
        case 0:
            ThEventHandler* client_initializer =
                new ClientInitializeHandler(ev, ServerManager::get_instance());
            break;
        case 1:
            // TODO: handler de movimiento
        default:
            std::cerr << "Dispatcher: No handler for: " << ev.get_json()
                      << std::endl;
            break;
    }
}

ThDispatcherHandler::~ThDispatcherHandler() {}
