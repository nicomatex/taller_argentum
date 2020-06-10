#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "entity_manager.h"

class EntityFactory {
   private:
   	EntityManager &e_manager;
   public:
   	EntityFactory(EntityManager &e_manager);
   	~EntityFactory();
   	Entity& createPlayer();
};

#endif // ENTITY_FACTORY_H