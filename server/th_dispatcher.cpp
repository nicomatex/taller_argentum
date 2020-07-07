#include "th_dispatcher.h"

#include "../include/nlohmann/json.hpp"
#include "events/attack_handler.h"
#include "events/change_map_handler.h"
#include "events/client_drop_handler.h"
#include "events/client_initializer_handler.h"
#include "events/command_handler.h"
#include "events/creation_handler.h"
#include "events/disconnect_handler.h"
#include "events/drop_loot_handler.h"
#include "events/inventory_handler.h"
#include "events/movement_handler.h"
#include "events/pickup_loot_handler.h"
#include "events/resuscitate_handler.h"
#include "events/unequip_handler.h"
#include "server_manager.h"

// Temp
#include <iostream>

void ThDispatcher::stop_and_join_handlers() {
    for (auto it : handlers) {
        if (it.second->is_threaded()) {
            BlockingThEventHandler* handler =
                static_cast<BlockingThEventHandler*>(it.second);
            handler->stop();
            handler->join();
        }
        delete it.second;
    }
}

void ThDispatcher::handle(Event& event) {
    try {
        nlohmann::json json_ev = event.get_json();
        int ev_id = json_ev["ev_id"];
        if (!handlers.count(ev_id)) {
            std::cerr << "Dispatcher: No handler for: " << json_ev << std::endl;
        } else {
            handlers[ev_id]->push_event(event);
        }
    } catch (const nlohmann::detail::exception& e) {
        std::cerr << "Dispatcher: error in json: " << event.get_json()
                  << std::endl;
    }
}

ThDispatcher::ThDispatcher() : BlockingThEventHandler() {
    std::cerr << "Dispatcher: starting.." << std::endl;
    handlers[static_cast<int>(SERVER_DROP_CLIENT)] =
        static_cast<EventHandler*>(new ClientDropHandler());
    handlers[static_cast<int>(SERVER_CHANGE_MAP)] =
        static_cast<EventHandler*>(new ChangeMapHandler());
    handlers[static_cast<int>(EV_ID_CONNECT)] =
        static_cast<EventHandler*>(new ClientInitializeHandler());
    handlers[static_cast<int>(EV_ID_DISCONNECT)] =
        static_cast<EventHandler*>(new DisconnectHandler());
    handlers[static_cast<int>(EV_ID_MOVE)] =
        static_cast<EventHandler*>(new MovementHandler());
    handlers[static_cast<int>(EV_ID_COMMAND)] =
        static_cast<EventHandler*>(new CommandHandler());
    handlers[static_cast<int>(EV_ID_ATTACK)] =
        static_cast<EventHandler*>(new AttackHandler());
    handlers[static_cast<int>(EV_ID_INVENTORY)] =
        static_cast<EventHandler*>(new InventoryHandler());
    handlers[static_cast<int>(EV_ID_CREATE)] =
        static_cast<EventHandler*>(new CreationHandler());
    handlers[static_cast<int>(EV_ID_PICKUP_LOOT)] =
        static_cast<EventHandler*>(new PickupLootHandler());
    handlers[static_cast<int>(EV_ID_DROP_LOOT)] =
        static_cast<EventHandler*>(new DropLootHandler());
    handlers[static_cast<int>(SERVER_RESUSCITATE)] =
        static_cast<EventHandler*>(new ResuscitateHandler());
    handlers[static_cast<int>(SERVER_UNEQUIP)] =
        static_cast<EventHandler*>(new UnequipHandler());
    // Inicializamos los handlers que sean threads
    for (auto it : handlers) {
        if (it.second->is_threaded()) {
            BlockingThEventHandler* handler =
                static_cast<BlockingThEventHandler*>(it.second);
            handler->start();
        }
    }
}
ThDispatcher::~ThDispatcher() {}

void ThDispatcher::stop() {
    BlockingThEventHandler::stop();
    stop_and_join_handlers();
}
