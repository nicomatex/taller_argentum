#include "entity.h"

#include <iostream>

Entity::Entity(EntityId id, const std::string& name,
               MovementComponent* movement_component,
               CombatComponent* combat_component)
    : id(id),
      name(name),
      movement_component(movement_component),
      combat_component(combat_component) {}

Entity::~Entity() {}

unsigned int Entity::get_id() const {
    return id;
}

std::string Entity::get_name() const {
    return name;
}

position_t Entity::get_facing_position(position_t position) {
    return movement_component->get_facing_position(position);
}

attack_result_t Entity::attack(Entity* attacked) {
    if (!combat_component->attack_ready())
        return {false, 0, 0, 0};
    damage_t raw_dmg = combat_component->attack();
    attack_result_t dealt = attacked->combat_component->receive_damage(raw_dmg);

    return dealt;
}

bool Entity::is_alive() const {
    return true;
}

void Entity::update(uint64_t delta_t) {}
