#include "map_monitor.h"

#include <atomic>

// Temp
#include <iostream>

MapMonitor::MapMonitor(nlohmann::json map_description) : map(map_description) {}

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

std::vector<nlohmann::json> MapMonitor::get_update_logs() {
    std::unique_lock<std::recursive_mutex> l(m);
    std::queue<nlohmann::json>& logs_queue = map.get_update_logs();
    std::vector<nlohmann::json> logs;
    while (!logs_queue.empty()) {
        logs.push_back(logs_queue.front());
        logs_queue.pop();
    }
    return logs;
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