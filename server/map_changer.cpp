#include "map_changer.h"

#include "event_factory.h"
#include "server_manager.h"

// Temp
#include <iostream>

MapChanger::MapChanger(nlohmann::json teleports) {
    for (auto& it : teleports.items()) {
        nlohmann::json& teleport = it.value();
        position_t position = it.value()["position"];
        position_t pos_dest = it.value()["destination"];
        MapId map_dest = it.value()["destination"]["map_id"];
        dest_position[position] = pos_dest;
        dest_map[position] = map_dest;
    }
}

MapChanger::~MapChanger() {}

void MapChanger::set_change_if_necessary(const std::string& name,
                                         position_t position) {
    if (!dest_position.count(position) || !dest_map.count(position))
        return;
    change_required.emplace(name, position);
}

void MapChanger::change_maps() {
    ServerManager& server_manager = ServerManager::get_instance();
    for (auto& it : change_required) {
        ClientId client_id = server_manager.get_client_by_name(it.first);
        nlohmann::json player_data = server_manager.rm_player(client_id);
        player_data["pos"] = dest_position.at(it.second);
        player_data["map_id"] = dest_map.at(it.second);
        server_manager.send_to(client_id, EventFactory::notify_map_change());
        server_manager.get_dispatcher().push_event(
            EventFactory::change_map(client_id, player_data));
    }
    change_required = std::unordered_map<std::string, position_t>();
}
