#include "map_monitor.h"

#include <atomic>

// Temp
#include <iostream>

MapMonitor::MapMonitor(nlohmann::json map_description)
    : map(map_description, map_changer),
      map_changer(map_description["changes"], map_description["height"],
                  map_description["width"]) {}

MapMonitor::~MapMonitor() {}

EntityId MapMonitor::add_player(ClientId client_id,
                                nlohmann::json player_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    EntityId entity_id = map.add_player(player_info);
    client_map[client_id] = entity_id;
    return entity_id;
}

nlohmann::json MapMonitor::rm_player(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    EntityId player_id = client_map.at(client_id);
    client_map.erase(client_id);
    return map.rm_player(player_id);
}

position_t MapMonitor::get_position(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    return map.get_position(client_map.at(client_id));
}

void MapMonitor::update(uint64_t delta_t) {
    std::unique_lock<std::recursive_mutex> l(m);
    map.update(delta_t);
    map_changer.change_maps();
}

void MapMonitor::push_action(ClientId client_id, Action* action) {
    std::unique_lock<std::recursive_mutex> l(m);
    map.push_action(client_map.at(client_id), action);
}

std::vector<nlohmann::json> MapMonitor::get_update_logs() {
    // TODO
    return std::vector<nlohmann::json>();
}

nlohmann::json MapMonitor::get_update_data(bool& update_entities) {
    nlohmann::json map_data;
    m.lock();
    PositionMap position_map_copy = map.get_position_map();
    if (update_entities || map.is_dirty()) {
        update_entities = true;
        map_data["entities"] = map.get_entity_data();
    }
    m.unlock();
    map_data["positions"] = Map::get_position_data(position_map_copy);
    return map_data;
}

nlohmann::json MapMonitor::get_map_data() {
    std::unique_lock<std::recursive_mutex> l(m);
    return map.get_map_data();
}