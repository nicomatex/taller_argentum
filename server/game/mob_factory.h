#ifndef MOB_FACTORY_H
#define MOB_FACTORY_H

#include <unordered_map>

#include "../../include/types.h"
#include "monster.h"
#include "npc.h"

class MobFactory {
   private:
    std::unordered_map<MobId, nlohmann::json> monsters_info;
    std::unordered_map<MobId, nlohmann::json> npcs_info;

   public:
    MobFactory(const char* mobs_path_file);
    ~MobFactory();

    Monster* create_monster(EntityId entity_id, MobId monster_id, Map& map);
    Npc* create_npc(EntityId entity_id, MobId npc_id, Map& map);
};

#endif  // MOB_FACTORY_H
