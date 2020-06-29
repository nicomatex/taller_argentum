#include "map_changer.h"

#include "../include/my_exception.h"
#include "events/event_factory.h"
#include "game/map.h"
#include "server_manager.h"

// Temp
#include <iostream>

MapChanger::MapChanger() {}
MapChanger::~MapChanger() {}

void MapChanger::push_change(map_change_t map_change) {
    changes_queue.push(map_change);
}

void MapChanger::change_maps() {
    ServerManager& server_manager = ServerManager::get_instance();
    while (!changes_queue.empty()) {
        map_change_t change = changes_queue.front();
        changes_queue.pop();
        ClientId client_id = server_manager.get_client_by_name(change.name);
        nlohmann::json player_data = server_manager.rm_player(client_id);
        player_data["map_id"] = change.map;
        player_data["pos"] = change.position;
        server_manager.send_to(client_id, EventFactory::notify_map_change());
        // TODO: VER SI SE PUEDE DEJAR server_manager.add_player()
        server_manager.get_dispatcher().push_event(
            EventFactory::change_map(client_id, player_data));
    }
}
