#include "race_graphics_manager.h"

#include <fstream>
#include <iostream>

#include "../../include/my_exception.h"
#include "../../include/nlohmann/json.hpp"

std::unordered_map<race_type_t, uint32_t> RaceGraphicsManager::race_heads_map;
std::unordered_map<race_type_t, uint32_t> RaceGraphicsManager::race_bodies_map;

RaceGraphicsManager::RaceGraphicsManager() {}

RaceGraphicsManager::~RaceGraphicsManager() {}

void RaceGraphicsManager::init(const char *races_file) {
    std::ifstream races_istream(races_file);
    if (!races_istream.is_open())
        throw MyException("RaceGraphicsManager: Error opening races g file: %s",
                          races_file);
    nlohmann::json json_races;
    races_istream >> json_races;
    for (auto &it : json_races["races"].items()) {
        nlohmann::json race_data = it.value();
        race_type_t race_type = race_data["type"];
        race_heads_map[race_type] = race_data["head_id"];
        race_bodies_map[race_type] = race_data["body_id"];
    }
}

uint32_t RaceGraphicsManager::get_race_head(race_type_t race_type) {
    if (!race_heads_map.count(race_type))
        throw MyException("RaceGraphicsManager: Race does not exist: %i",
                          race_type);
    return race_heads_map.at(race_type);
}

uint32_t RaceGraphicsManager::get_race_body(race_type_t race_type) {
    if (!race_bodies_map.count(race_type))
        throw MyException("RaceGraphicsManager: Race does not exist: %i",
                          race_type);
    return race_bodies_map.at(race_type);
}