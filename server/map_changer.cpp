#include "map_changer.h"

#include "../include/blocking_queue.h"
#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "events/event_factory.h"
#include "game/map_transitions.h"
#include "server_manager.h"

// Temp
#include <iostream>

MapChanger::MapChanger(MapManager& map_manager)
    : Thread(), map_manager(map_manager) {}
MapChanger::~MapChanger() {}

void MapChanger::run() {
    ServerManager& server_manager = ServerManager::get_instance();
    try {
        while (true) {
            map_change_t map_change = map_manager.get_change();
            ClientId client_id =
                server_manager.get_client_by_name(map_change.name);
            server_manager.get_dispatcher().push_event(EventFactory::change_map(
                client_id, {{"new_map_id", map_change.map},
                            {"new_pos", map_change.position}}));
        }
    } catch (const ClosedBlockingQueueException& e) {
    } catch (const std::exception& e) {
        std::cerr << "MapChanger: " << e.what() << std::endl;
    }
}
