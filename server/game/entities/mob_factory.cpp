#include "mob_factory.h"

#include <fstream>

#include "../../../include/my_exception.h"
#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"
#include "banker.h"
#include "healer.h"
#include "merchant.h"

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
        monsters_names.emplace(monster_info["name"], monster_info["id"]);
    }

    for (auto& it : mobs["npcs"].items()) {
        nlohmann::json npc_info = it.value();
        npcs_info.emplace(npc_info["id"], npc_info);
        npcs_by_profession.emplace(npc_info["profession"], npc_info["id"]);
    }
}

MobFactory::~MobFactory() {}

Monster* MobFactory::create_monster(EntityId entity_id,
                                    const std::string& monster_name, Map& map) {
    if (!monsters_names.count(monster_name))
        throw MyException("MobFactory: Monster does not exist: %s",
                          monster_name);
    MobId mob_id = monsters_names.at(monster_name);
    nlohmann::json info = monsters_info.at(mob_id);
    return new Monster(entity_id, info, map);
}

Monster* MobFactory::create_monster(EntityId entity_id, MobId monster_id,
                                    Map& map) {
    if (!monsters_info.count(monster_id))
        throw MyException("MobFactory: Monster does not exist: %i", monster_id);
    return new Monster(entity_id, monsters_info.at(monster_id), map);
}

Npc* MobFactory::create_npc(EntityId entity_id, npc_proffesion_t npc_proffesion,
                            Map& map) {
    if (!npcs_by_profession.count(npc_proffesion))
        throw MyException("MobFactory: Npc's profession does not exist: %i",
                          npc_proffesion);
    Npc* npc = nullptr;
    MobId npc_id = npcs_by_profession.at(npc_proffesion);
    switch (npc_proffesion) {
        case HEALER:
            npc = new Healer(entity_id, npcs_info[npc_id], map);
            break;
        case MERCHANT:
            npc = new Merchant(entity_id, npcs_info[npc_id], map);
            break;
        case BANKER:
            npc = new Banker(entity_id, npcs_info[npc_id], map);
            break;
    }
    return npc;
}

Npc* MobFactory::create_npc(EntityId entity_id, MobId npc_id, Map& map) {
    if (!npcs_info.count(npc_id))
        throw MyException("MobFactory: Npc does not exist: %i", npc_id);
    Npc* npc = nullptr;
    nlohmann::json& npc_info = npcs_info.at(npc_id);
    switch ((npc_proffesion_t)npc_info["profession"]) {
        case HEALER:
            npc = new Healer(entity_id, npc_info, map);
            break;
        case MERCHANT:
            npc = new Merchant(entity_id, npc_info, map);
            break;
        case BANKER:
            npc = new Banker(entity_id, npc_info, map);
            break;
    }
    return npc;
}
