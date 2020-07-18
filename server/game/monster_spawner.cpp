#include "monster_spawner.h"

#include "configuration_manager.h"
#include "entities/mob_factory.h"
#include "map.h"
#include "random_event_generator.h"

// Temp
#include <iostream>

std::unordered_map<std::string, int> MonsterSpawner::search_monsters() {
    std::unordered_map<std::string, int> monster_count{};
    for (auto& it : map.entity_matrix) {
        if (!it.second || it.second->get_type() != MONSTER)
            continue;
        if (!monster_count.count(it.second->get_name()))
            monster_count.emplace(it.second->get_name(), 0);
        monster_count.at(it.second->get_name())++;
    }
    return monster_count;
}

MonsterSpawner::MonsterSpawner(Map& map, const nlohmann::json& spawn_list)
    : map(map), accumulator(ConfigurationManager::get_spawn_interval()) {
    if (map.is_safe())
        return;
    for (auto& it : spawn_list.items()) {
        const nlohmann::json& monster = it.value();
        spawn_points.emplace(
            monster["mob_name"],
            std::make_pair(monster["max_count"], monster["pos"]));
    }
}

MonsterSpawner::~MonsterSpawner() {}

void MonsterSpawner::update(uint64_t delta_t) {
    accumulator += delta_t;
    if (accumulator < ConfigurationManager::get_spawn_interval())
        return;
    accumulator = 0;
    std::unordered_map<std::string, int> monster_count = search_monsters();
    for (auto& it : spawn_points) {
        auto& pair = it.second;
        if (!monster_count.count(it.first)) {
            monster_count.emplace(it.first, 0);
        }
        if (monster_count.at(it.first) < pair.first) {
            Monster* monster = map.entity_factory.create_monster(it.first);
            position_t pos = pair.second;
            pos = {RandomEventGenerator::random_in(pos.x - 3, pos.x + 3),
                   RandomEventGenerator::random_in(pos.y - 3, pos.y + 3)};
            map.add_entity(monster, pos);
            monster_count[it.first]++;
        }
    }
}
