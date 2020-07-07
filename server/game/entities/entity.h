#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"
#include "../position.h"
#include "components/combat_component.h"
#include "components/experience_component.h"
#include "components/movement_component.h"

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
           CombatComponent* combat_component, unsigned int current_level,
           unsigned int current_exp);
    Entity(EntityId id, const std::string& name, unsigned int current_level,
           unsigned int current_exp);
    virtual ~Entity();

    virtual void die() = 0;
    virtual bool is_alive() const = 0;

    std::string get_name() const;
    unsigned int get_level() const;
    unsigned int get_max_hp() const;

    virtual entity_type_t get_type() const = 0;
    virtual nlohmann::json get_data() const = 0;
    virtual void update(uint64_t delta_t) = 0;

    virtual position_t get_facing_position(position_t position);

    virtual bool can_attack(Entity* attacked) const;
    attack_result_t attack(Entity* attacked);

    EntityId get_id() const;
};

#endif  // ENTITY_H