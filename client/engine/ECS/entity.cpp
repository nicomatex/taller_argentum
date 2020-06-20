#include "entity.h"

Entity::Entity(unsigned int id) : id(id), alive(true) {}

Entity::~Entity() {}

void Entity::update() {
	for (auto& comp : components) {
		comp.second->update();
	}
}

bool Entity::is_alive() {
	return alive;
}

void Entity::kill() {
	alive = false;
}
