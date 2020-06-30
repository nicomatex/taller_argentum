#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "combat_component.h"
#include "movement_component.h"
#include "position.h"

enum entity_type_t { PLAYER, NPC, MONSTER };

class Entity {
   protected:
    EntityId id;
    const std::string name;

    MovementComponent* movement_component;
    CombatComponent* combat_component;

   public:
    Entity(EntityId id, const std::string& name,
           MovementComponent* movement_component,
           CombatComponent* combat_component);
    virtual ~Entity();

    /* Saber el tipo de la entidad sirve para saber si es colisionable o no.
    Los players y npcs son colisionables; el loot no.*/
    virtual entity_type_t get_type() const = 0;

    std::string get_name() const;

    virtual nlohmann::json get_data() const = 0;
    virtual void update(uint64_t delta_t);

    virtual position_t get_facing_position(position_t position);

    attack_result_t attack(Entity* attacked);

    EntityId get_id() const;
};

#endif  // ENTITY_H