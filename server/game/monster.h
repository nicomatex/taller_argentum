#ifndef MONSTER_H
#define MONSTER_H

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "entity.h"

class Map;

class Monster : public Entity {
   private:
    Map& map;
    uint32_t sprite_id;
    bool alive;

   public:
    Monster(EntityId entity_id, nlohmann::json monster_info, Map& map);

    entity_type_t get_type() const override;

    nlohmann::json get_data() const override;

    void die() override;
    bool is_alive() const override;

    void update(uint64_t delta_t) override;
};

#endif  // MONSTER_H
