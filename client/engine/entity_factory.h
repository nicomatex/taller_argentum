#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../../include/nlohmann/json.hpp"
#include "ECS/entity.h"
#include "ECS/entity_manager.h"

class EntityFactory {
   private:
   public:
    static Entity &create_player(nlohmann::json entity_info);
    static Entity &create_npc(nlohmann::json entity);
};

#endif  // ENTITY_FACTORY_H