#include "entity.h"

#include <iostream>

Entity::Entity(EntityId id, MovementComponent* movement_component,
               CombatComponent* combat_component)
    : id(id),
      movement_component(movement_component),
      combat_component(combat_component) {}

Entity::~Entity() {}

unsigned int Entity::get_id() const {
    return id;
}

position_t Entity::get_facing_position(position_t position) {
    return movement_component->get_facing_position(position);
}

void Entity::update(uint64_t delta_t) {}
