#include "map_monitor.h"

MapMonitor::MapMonitor(nlohmann::json map_description) : map(map_description) {}

MapMonitor::~MapMonitor() {}

EntityId MapMonitor::add_player(ClientId client_id,
                                nlohmann::json player_info) {
    std::unique_lock<std::mutex> l(m);
    EntityId entity_id = map.add_player(player_info);
    client_map[client_id] = entity_id;
    return entity_id;
}

void MapMonitor::update(uint64_t delta_t) {
    std::unique_lock<std::mutex> l(m);
    map.update(delta_t);
}

void MapMonitor::with_player(ClientId client_id, const Action& action) {
    std::unique_lock<std::mutex> l(m);
    map.with_entity(client_map.at(client_id), action);
}

nlohmann::json MapMonitor::get_position_data() {
    m.lock();
    PositionMap copy = map.get_position_map();
    m.unlock();
    return Map::get_position_data(copy);
}

nlohmann::json MapMonitor::get_entity_data() {
    std::unique_lock<std::mutex> l(m);
    return map.get_entity_data();
}

nlohmann::json MapMonitor::get_map_data() {
    std::unique_lock<std::mutex> l(m);
    return map.get_map_data();
}