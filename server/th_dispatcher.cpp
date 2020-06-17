#include "th_dispatcher.h"

#include "../nlohmann/json.hpp"
#include "client_initializer_handler.h"
#include "movement_handler.h"
#include "server_manager.h"
#include "th_event_handler.h"

// Temp
#include <iostream>

ThDispatcher::ThDispatcher() {}

void ThDispatcher::handle(Event& ev) {
    nlohmann::json json_ev = ev.get_json();
    std::cerr << "Dispatcher got: " << json_ev << std::endl;
    ThEventHandler* handler;
    int ev_id = json_ev["ev_id"];
    switch (ev_id) {
        case 0:
            handler = new ClientInitializeHandler(ev);
            break;
        case 2:
            handler = new MovementHandler(ev);
            break;
        default:
            std::cerr << "Dispatcher: No handler for: " << ev.get_json()
                      << std::endl;
            break;
    }
    handler->start();
    handler->join();
}

ThDispatcher::~ThDispatcher() {}