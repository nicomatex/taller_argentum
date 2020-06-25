#include "map_changer.h"

#include "../include/my_exception.h"
#include "event_factory.h"
#include "map.h"
#include "server_manager.h"

// Temp
#include <iostream>

bool MapChanger::requires_map_change(position_t position) {
    return dest_position.count(position) || dest_map.count(position) ||
           position.x < 0 || position.x >= width || position.y < 0 ||
           position.y >= height;
}

position_t MapChanger::get_dest_position(position_t position) {
    if (dest_position.count(position)) {
        return dest_position.at(position);
    } else if (position.x < 0) {
        return {width - 1, position.y};
    } else if (position.x >= width) {
        return {0, position.y};
    } else if (position.y < 0) {
        return {position.x, height - 1};
    } else if (position.y >= height) {
        return {position.x, 0};
    }
    throw MyException("La posición no tiene un destino válido.");
    return {width / 2, height / 2};
}

MapId MapChanger::get_dest_map(position_t position) {
    if (dest_map.count(position)) {
        return dest_map.at(position);
    } else if (position.x < 0) {
        return left_map;
    } else if (position.x >= width) {
        return right_map;
    } else if (position.y < 0) {
        return upper_map;
    } else if (position.y >= height) {
        return lower_map;
    }
    throw MyException("La posición no tiene un destino válido.");
    return 0;
}

MapChanger::MapChanger(nlohmann::json changes, int height, int width)
    : height(height), width(width) {
    for (auto& it : changes["teleports"].items()) {
        nlohmann::json& teleport = it.value();
        position_t position = it.value()["position"];
        position_t pos_dest = it.value()["destination"];
        MapId map_dest = it.value()["destination"]["map_id"];
        dest_position[position] = pos_dest;
        dest_map[position] = map_dest;
    }
    upper_map = changes["upper"];
    lower_map = changes["lower"];
    right_map = changes["right"];
    left_map = changes["left"];
}
MapChanger::~MapChanger() {}

void MapChanger::set_change_if_necessary(const std::string& name,
                                         position_t position) {
    if (requires_map_change(position))
        change_required.emplace(name, position);
    return;
}

void MapChanger::change_maps() {
    ServerManager& server_manager = ServerManager::get_instance();
    for (auto& it : change_required) {
        ClientId client_id = server_manager.get_client_by_name(it.first);
        nlohmann::json player_data = server_manager.rm_player(client_id);
        player_data["pos"] = get_dest_position(it.second);
        std::cerr << player_data << std::endl;
        player_data["map_id"] = get_dest_map(it.second);
        server_manager.send_to(client_id, EventFactory::notify_map_change());
        server_manager.get_dispatcher().push_event(
            EventFactory::change_map(client_id, player_data));
    }
    change_required = std::unordered_map<std::string, position_t>();
}
