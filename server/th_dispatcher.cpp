#include "th_dispatcher.h"

#include "../nlohmann/json.hpp"
#include "client_drop_handler.h"
#include "client_initializer_handler.h"
#include "command_handler.h"
#include "movement_handler.h"
#include "server_manager.h"
#include "th_event_handler.h"

// Temp
#include <iostream>

ThDispatcher::ThDispatcher() {}

void ThDispatcher::handle(Event& ev) {
    try {
        nlohmann::json json_ev = ev.get_json();
        std::cerr << "Dispatcher got: " << json_ev << std::endl;
        ThEventHandler* handler;
        int ev_id = json_ev["ev_id"];
        switch (ev_id) {
            case EV_ID_DROP_CLIENT:
                handler = new ClientDropHandler(ev);
                break;
            case EV_ID_CONNECT:
                handler = new ClientInitializeHandler(ev);
                break;
            case EV_ID_MOVE:
                handler = new MovementHandler(ev);
                break;
            case EV_ID_COMMAND:
                handler = new CommandHandler(ev);
                break;
            default:
                std::cerr << "Dispatcher: No handler for: " << json_ev
                          << std::endl;
                break;
        }
        handler->start();
        handler->join();
    } catch (const std::exception& e) {
        std::cerr << "dispatcher: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "dispatcher: Unknown exception" << std::endl;
    }
}

ThDispatcher::~ThDispatcher() {}
