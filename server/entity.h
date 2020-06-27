#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "combat_component.h"
#include "movement_component.h"
#include "position.h"

enum entity_type_t { PLAYER, NPC, MONSTER };

class Entity {
   protected:
    EntityId id;
    MovementComponent* movement_component;
    CombatComponent* combat_component;

   public:
    Entity(EntityId id, MovementComponent* movement_component,
           CombatComponent* combat_component);
    virtual ~Entity();

    /* Saber el tipo de la entidad sirve para saber si es colisionable o no.
    Los players y npcs son colisionables; el loot no.*/
    virtual entity_type_t get_type() const = 0;

    virtual nlohmann::json get_data() const = 0;
    virtual void update(uint64_t delta_t);

    virtual position_t get_facing_position(position_t position);

    // virtual int attack(Entity* attacked) = 0;
    // virtual int recv_damage(int raw_damage) = 0;

    EntityId get_id() const;
};

#endif  // ENTITY_H