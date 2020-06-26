#ifndef __ENTITY_H
#define __ENTITY_H

#include <cstdint>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "position.h"

enum entity_type_t { PLAYER, NPC };

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

    virtual nlohmann::json get_data() = 0;
    virtual void update(uint64_t delta_t);

    virtual position_t get_facing_position(position_t position) = 0;

    // virtual int attack(Entity* attacked) = 0;
    // virtual int recv_damage(int raw_damage) = 0;

    EntityId get_id() const;
};

#endif