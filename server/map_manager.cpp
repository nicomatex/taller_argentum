#include "map_manager.h"

#include <fstream>
#include <tuple>
#include <utility>

// Temp
#include <iostream>

MapManager::MapManager(const char* path) {
    std::ifstream index_file(path);
    nlohmann::json maps_index = nlohmann::json::parse(index_file);
    for (auto& it : maps_index["maps"].items()) {
        nlohmann::json map_info = it.value();
        std::ifstream map_file(map_info["path"]);
        nlohmann::json map_description = nlohmann::json::parse(map_file);
        MapId map_id = map_info["map_id"];
        maps.emplace(
            std::piecewise_construct, std::forward_as_tuple(map_id),
            std::forward_as_tuple(map_id, map_description, map_info["mobs"],
                                  map_info["transitions"]));
        std::cerr << "MapManager: creado mapa: " << map_info["map_name"]
                  << std::endl;
    }
}

MapManager::~MapManager() {}

MapMonitor& MapManager::operator[](MapId map_id) {
    return maps.at(map_id);
}

const std::vector<MapId> MapManager::get_ids() {
    std::vector<MapId> vector;
    for (auto& it : maps) {
        vector.push_back(it.first);
    }
    return vector;
}

void MapManager::update(uint64_t delta_t) {
    for (auto& it : maps) {
        it.second.update(delta_t);
        std::queue<map_change_t> q = it.second.get_transitions();
        while (!q.empty()) {
            map_change_t change = q.front();
            q.pop();
            changes_queue.push(change);
        }
    }
}

map_change_t MapManager::get_change() {
    return changes_queue.pop();
}
