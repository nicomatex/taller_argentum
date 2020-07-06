#include "entity.h"

#include <algorithm>

// Temp
#include <iostream>

#define MAX_LEVEL_DIFERENCE 10

Entity::Entity(EntityId id, const std::string& name,
               MovementComponent* movement_component,
               CombatComponent* combat_component, unsigned int current_level,
               unsigned int current_exp)
    : id(id),
      name(name),
      movement_component(movement_component),
      combat_component(combat_component),
      experience_component(current_level, current_exp) {}

Entity::Entity(EntityId id, const std::string& name, unsigned int current_level,
               unsigned int current_exp)
    : id(id), name(name), experience_component(current_level, current_exp) {}

Entity::~Entity() {
    delete movement_component;
    delete combat_component;
}

unsigned int Entity::get_id() const {
    return id;
}

std::string Entity::get_name() const {
    return name;
}

unsigned int Entity::get_level() const {
    return experience_component.get_level();
}

unsigned int Entity::get_max_hp() const {
    return combat_component->get_max_hp();
}

position_t Entity::get_facing_position(position_t position) {
    return movement_component->get_facing_position(position);
}

attack_result_t Entity::attack(Entity* attacked) {
    if (!combat_component->attack_ready())
        return {false, 0, 0, 0};
    damage_t raw_dmg = combat_component->attack();
    attack_result_t dealt = attacked->combat_component->receive_damage(raw_dmg);
    experience_component.add_exp(
        dealt.damage_dealt *
        std::max<int>(attacked->get_level() - get_level() + MAX_LEVEL_DIFERENCE,
                      0));
    if (dealt.killed) {
        experience_component.add_exp(
            /*(RAND * )*/ attacked->get_max_hp() *
            std::max<int>(
                attacked->get_level() - get_level() + MAX_LEVEL_DIFERENCE, 0));
    }
    return dealt;
}
