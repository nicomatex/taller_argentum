#include "map_manager.h"

#include <fstream>

MapManager::MapManager(const char* path) {
    std::ifstream input_file(path);
    nlohmann::json map_description = nlohmann::json::parse(input_file);
    maps.emplace(0, map_description);
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
