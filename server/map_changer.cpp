#include "map_changer.h"

#include "../include/my_exception.h"
#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "events/event_factory.h"
#include "game/position.h"
#include "server_manager.h"

// Temp
#include <iostream>

MapChanger::MapChanger() {}
MapChanger::~MapChanger() {}

void MapChanger::push_change(map_change_t map_change) {
    ServerManager& server_manager = ServerManager::get_instance();
    ClientId client_id = server_manager.get_client_by_name(map_change.name);
    server_manager.get_dispatcher().push_event(EventFactory::change_map(
        client_id,
        {{"new_map_id", map_change.map}, {"new_pos", map_change.position}}));
}
