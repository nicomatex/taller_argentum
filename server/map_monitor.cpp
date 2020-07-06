#include "map_monitor.h"

#include <atomic>

// Temp
#include <iostream>

MapMonitor::MapMonitor(nlohmann::json map_description) : map(map_description) {}

MapMonitor::~MapMonitor() {}

nlohmann::json MapMonitor::add_player(ClientId client_id,
                                      nlohmann::json player_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    nlohmann::json data = map.add_player(player_info);
    client_map[client_id] = data["entity_id"];
    return data;
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

std::queue<map_change_t> MapMonitor::get_transitions() {
    std::unique_lock<std::recursive_mutex> l(m);
    std::queue<map_change_t>& map_changes_ref = map.get_transitions();
    std::queue<map_change_t> changes;
    while (!map_changes_ref.empty()) {
        changes.push(map_changes_ref.front());
        map_changes_ref.pop();
    }
    l.unlock();
    return changes;
}

void MapMonitor::update(uint64_t delta_t) {
    std::unique_lock<std::recursive_mutex> l(m);
    map.update(delta_t);
}

void MapMonitor::push_action(ClientId client_id, Action* action) {
    std::unique_lock<std::recursive_mutex> l(m);
    map.push_action(client_map.at(client_id), action);
}

std::vector<map_log_t> MapMonitor::get_update_logs() {
    std::unique_lock<std::recursive_mutex> l(m);
    std::queue<map_log_t>& logs_queue = map.get_update_logs();
    std::vector<map_log_t> logs;
    while (!logs_queue.empty()) {
        logs.push_back(logs_queue.front());
        logs_queue.pop();
    }
    return logs;
}

bool MapMonitor::dirty_entities() const {
    return map.dirty_entities();
}
bool MapMonitor::dirty_loot() const {
    return map.dirty_loot();
}

nlohmann::json MapMonitor::get_update_data(bool forced_update) {
    nlohmann::json map_data;
    std::unique_lock<std::recursive_mutex> l(m);
    PositionMap position_map_copy = map.get_position_map();
    if (map.dirty_entities() || forced_update) {
        map_data["entities"] = map.get_entity_data();
    }
    if (map.dirty_loot() || forced_update) {
        map_data["items"] = map.get_loot_data();
    }
    l.unlock();
    map_data["positions"] = Map::get_position_data(position_map_copy);
    return map_data;
}

nlohmann::json MapMonitor::get_map_data() {
    std::unique_lock<std::recursive_mutex> l(m);
    return map.get_map_data();
}