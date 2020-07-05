#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "combat_component.h"
#include "movement_component.h"
#include "experience_component.h"
#include "position.h"


class Entity {
   protected:
    EntityId id;
    const std::string name;

    MovementComponent* movement_component;
    CombatComponent* combat_component;
    ExperienceComponent experience_component;

   public:

    Entity(EntityId id, const std::string& name,
           MovementComponent* movement_component,
           CombatComponent* combat_component,
           unsigned int current_level, unsigned int current_exp);
    Entity(EntityId id, const std::string& name, unsigned int current_level, unsigned int current_exp);
    virtual ~Entity();

    /* Saber el tipo de la entidad sirve para saber si es colisionable o no.
    Los players y npcs son colisionables; el loot no.*/

    std::string get_name() const;

    virtual entity_type_t get_type() const = 0;
    virtual nlohmann::json get_data() const = 0;
    virtual void update(uint64_t delta_t) = 0;

    virtual position_t get_facing_position(position_t position);

    attack_result_t attack(Entity* attacked);

    virtual bool is_alive() const;
    EntityId get_id() const;
};

#endif  // ENTITY_H