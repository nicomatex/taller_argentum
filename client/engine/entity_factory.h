#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../../nlohmann/json.hpp"
#include "ECS/entity.h"
#include "ECS/entity_manager.h"

class EntityFactory {
   private:
   public:
    static Entity &create_player(nlohmann::json entity_info);
    static Entity &create_player(unsigned int entity_id, int head_id,
                                 int body_id, int weapon_id, int shield_id,
                                 int helmet_id, int armor_id);
};

#endif  // ENTITY_FACTORY_H