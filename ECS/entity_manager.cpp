#include "entity_manager.h"
#include "entity.h"

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

static unsigned int get_new_id() {
	static unsigned int entity_id = 0;
	return entity_id++;
}

void EntityManager::update(int dt) {
	for(auto& entity : entities) entity.second->update(dt);

}

void EntityManager::draw() {
	for(auto& entity : entities) entity.second->draw();
}

Entity& EntityManager::create() {
	unsigned int entity_id = get_new_id();
	entities[entity_id] = std::unique_ptr<Entity>(new Entity(entity_id));
	return *entities.at(entity_id);
}

void EntityManager::clean() {
	for (auto it = entities.begin(); it != entities.end();) {
   		if (!(*it).second->is_alive()) it = entities.erase(it);
   		else it++;
	}
}

bool EntityManager::has_entity(unsigned int entity_id) {
	return entities.count(entity_id);
}

Entity& EntityManager::get_from_id(unsigned int entity_id) {
	if (!has_entity(entity_id)) throw std::exception();
	return *entities.at(entity_id);
}
