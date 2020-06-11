#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "ECS/entity_manager.h"
#include "ECS/entity.h"

class EntityFactory {
   private:
   	EntityManager &e_manager;
   public:
   	EntityFactory(EntityManager &e_manager);
   	~EntityFactory();
   	Entity& create_player(int head_id, int body_id, int weapon_id, int offhand_id);
};

#endif // ENTITY_FACTORY_H