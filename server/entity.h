#ifndef __ENTITY_H
#define __ENTITY_H

#include <cstdint>

#include "../include/types.h"
#include "../nlohmann/json.hpp"

enum entity_type_t { PLAYER, NPC, LOOT };

class Entity {
   protected:
    EntityId id;
    nlohmann::json visual_entity_info;

   public:
    Entity(EntityId id);
    virtual ~Entity();

    /* Saber el tipo de la entidad sirve para saber si es colisionable o no.
    Los players y npcs son colisionables; el loot no.*/
    virtual entity_type_t get_type() = 0;

    nlohmann::json get_data();
    virtual void update(uint64_t delta_t);

    EntityId get_id() const;
};

#endif