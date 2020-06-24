#include "entity.h"

#include <iostream>

Entity::Entity(EntityId id) : id(id) {
    visual_entity_info["entity_id"] = id;
}

Entity::~Entity() {}

unsigned int Entity::get_id() const {
    return id;
}

void Entity::update(uint64_t delta_t) {}
