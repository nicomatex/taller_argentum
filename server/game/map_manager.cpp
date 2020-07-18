#include "map_manager.h"

#include <fstream>
#include <iostream>
#include <tuple>
#include <utility>

MapManager::MapManager(const char* index_path) : index_path(index_path) {}

MapManager::~MapManager() {}

void MapManager::create_maps() {
    std::ifstream index_file(index_path);
    nlohmann::json maps_index = nlohmann::json::parse(index_file);
    for (auto& it : maps_index["maps"].items()) {
        nlohmann::json map_info = it.value();
        std::ifstream map_file(map_info["path"]);
        nlohmann::json map_description = nlohmann::json::parse(map_file);
        MapId map_id = map_info["map_id"];
        const std::string& map_name = map_info["map_name"];
        maps.emplace(std::piecewise_construct, std::forward_as_tuple(map_id),
                     std::forward_as_tuple(
                         map_id, map_name, map_info["is_safe"], map_description,
                         map_info["mobs"], map_info["transitions"]));
        std::cerr << "MapManager: creado mapa: " << map_info["map_name"]
                  << std::endl;
    }
}

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
