#ifndef NPC_H
#define NPC_H

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "entity.h"
#include "map.h"

class Npc : public Entity {
  private:
    Map& map;
    uint32_t sprite_id;

   public:
    Npc(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Npc();

    entity_type_t get_type() const override;

    nlohmann::json get_data() const override;

    virtual void update(uint64_t delta_t) = 0;
};

#endif  // NPC_H