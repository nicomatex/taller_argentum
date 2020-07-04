#ifndef MONSTER_FACTORY_H
#define MONSTER_FACTORY_H

#include <unordered_map>

#include "../../include/types.h"
#include "monster.h"

class MonsterFactory {
   private:
    std::unordered_map<MonsterId, nlohmann::json> monsters_info;

   public:
    MonsterFactory(const char* monsters_path_file);
    ~MonsterFactory();

    Monster* create_monster(EntityId entity_id, MonsterId monster_id, Map& map);
};

#endif  // MONSTER_FACTORY_H
