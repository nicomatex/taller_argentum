#include "th_dispatcher.h"

#include "../include/nlohmann/json.hpp"
#include "events/attack_handler.h"
#include "events/change_map_handler.h"
#include "events/client_drop_handler.h"
#include "events/client_initializer_handler.h"
#include "events/command_handler.h"
#include "events/movement_handler.h"
#include "server_manager.h"

// Temp
#include <iostream>

void ThDispatcher::join_done(bool wait) {
    std::unique_lock<std::mutex> l(m);
    for (auto it = started_handlers.begin(); it != started_handlers.end();) {
        ThEventHandler* handler = *it;
        if (!wait && !handler->is_done()) {
            it++;
            continue;
        }
        handler->join();
        it = started_handlers.erase(it);
        delete handler;
    }
}

ThDispatcher::ThDispatcher() {}
ThDispatcher::~ThDispatcher() {}

void ThDispatcher::handle(Event& ev) {
    try {
        nlohmann::json json_ev = ev.get_json();
        ThEventHandler* handler = nullptr;
        int ev_id = json_ev["ev_id"];
        switch (ev_id) {
            case SERVER_DROP_CLIENT:
                handler = new ClientDropHandler(ev);
                break;
            case EV_ID_DISCONNECT:
                ServerManager::get_instance().drop_client(json_ev["client_id"]);
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
            case SERVER_CHANGE_MAP:
                handler = new ChangeMapHandler(ev);
                break;
            case EV_ID_ATTACK:
                handler = new AttackHandler(ev);
                break;
            case 1000:
                stop();
                join_done(true);
                break;
            default:
                std::cerr << "Dispatcher: No handler for: " << json_ev
                          << std::endl;
                break;
        }
        if (handler) {
            std::unique_lock<std::mutex> l(m);
            handler->start();
            started_handlers.push_back(handler);
        }
        join_done(false);
    } catch (const nlohmann::detail::exception& e) {
        std::cerr << "Dispatcher: error in json: " << ev.get_json()
                  << std::endl;
    }
}
