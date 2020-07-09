#include "mob_factory.h"

#include <fstream>

#include "../../include/my_exception.h"
#include "../../include/nlohmann/json.hpp"

// Temp
#include <iostream>

MobFactory::MobFactory(const char* mobs_path_file) {
    std::ifstream mobs_stream(mobs_path_file);
    if (!mobs_stream.is_open())
        throw MyException("MobFactory: Error opening mobs file: %s",
                          mobs_path_file);
    nlohmann::json mobs = nlohmann::json::parse(mobs_stream);
    for (auto& it : mobs["monsters"].items()) {
        nlohmann::json monster_info = it.value();
        monsters_info.emplace(monster_info["id"], monster_info);
        std::cerr << "MobFactory: reading monster: " << monster_info["name"]
                  << std::endl;
    }

    for (auto& it : mobs["npcs"].items()) {
        nlohmann::json npc_info = it.value();
        npcs_info.emplace(npc_info["id"], npc_info);
        std::cerr << "MobFactory: reading npc: " << npc_info["name"]
                  << std::endl;
    }
}
MobFactory::~MobFactory() {}

Monster* MobFactory::create_monster(EntityId entity_id, MobId monster_id,
                                    Map& map) {
    if (!monsters_info.count(monster_id))
        throw MyException("MobFactory: Monster does not exist: %i", monster_id);
    return new Monster(entity_id, monsters_info.at(monster_id), map);
}

Npc* MobFactory::create_npc(EntityId entity_id, MobId npc_id, Map& map) {
    if (!npcs_info.count(npc_id))
        throw MyException("MobFactory: Npc does not exist: %i", npc_id);
    return new Npc(entity_id, npcs_info.at(npc_id), map);
}
