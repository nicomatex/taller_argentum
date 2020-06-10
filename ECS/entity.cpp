#include "entity.h"

Entity::Entity(unsigned int id) : id(id), alive(true) {}

Entity::~Entity() {}

void Entity::update(int dt) {
	for (auto& comp : components) {
		comp.second->update(dt);
	}
}

void Entity::draw(){
	for (auto& comp : components) {
		comp.second->draw();
	}
}

bool Entity::is_alive() {
	return alive;
}

void Entity::kill() {
	alive = false;
}
