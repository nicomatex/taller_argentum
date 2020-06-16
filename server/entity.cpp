#include "entity.h"

Entity::Entity(unsigned int id) : id(id) {}

Entity::~Entity() {}

unsigned int Entity::get_id() const {
    return id;
}

void Entity::update(uint64_t delta_t) {}
