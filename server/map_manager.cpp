#include "map_manager.h"

#include <fstream>

// Temp
#include <iostream>

MapManager::MapManager(const char* path) {
    std::ifstream index_file(path);
    nlohmann::json maps_index = nlohmann::json::parse(index_file);
    for (auto& it : maps_index["maps"].items()) {
        nlohmann::json map_info = it.value();
        std::ifstream map_file(map_info["path"]);
        nlohmann::json map_description = nlohmann::json::parse(map_file);
        maps.emplace(map_info["map_id"], map_description);
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
    }
}

MapManager::~MapManager() {}
