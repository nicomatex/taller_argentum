#ifndef __ACTION_H
#define __ACTION_H

#include "entity.h"
#include "position.h"

class Map;

class Action {
   protected:
    static Entity* get_entity(Map& map, EntityId entity_id);

    static Entity* get_entity(Map& map, position_t position);

   public:
    virtual ~Action();
    virtual void execute(Map& map, EntityId entity_id) const = 0;
};

#endif