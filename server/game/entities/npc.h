#ifndef NPC_H
#define NPC_H

#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"
#include "entity.h"

class Map;

class Npc : public Entity {
   private:
    Map& map;
    uint32_t sprite_id;

   public:
    Npc(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Npc();

    void die() override;

    bool is_alive() const override;

    entity_type_t get_type() const override;

    nlohmann::json get_data() const override;

    void update(uint64_t delta_t) override;
};

#endif  // NPC_H