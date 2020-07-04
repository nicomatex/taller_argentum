#include "monster_factory.h"

#include <fstream>

#include "../../include/nlohmann/json.hpp"

// Temp
#include <iostream>

MonsterFactory::MonsterFactory(const char* monsters_path_file) {
    std::ifstream index_file(monsters_path_file);
    nlohmann::json monsters = nlohmann::json::parse(index_file);
    for (auto& it : monsters["monsters"].items()) {
        nlohmann::json monster_info = it.value();
        monsters_info.emplace(monster_info["id"], monster_info);
        std::cerr << "MonsterFactory: added: " << monster_info << std::endl;
    }
}
MonsterFactory::~MonsterFactory() {}

Monster* MonsterFactory::create_monster(EntityId entity_id,
                                        MonsterId monster_id, Map& map) {
    return new Monster(entity_id, monsters_info.at(monster_id), map);
}
