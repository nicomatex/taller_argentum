#include "entity_manager.h"
#include "entity.h"

EntityManager& EntityManager::get_instance(){
	static EntityManager instance;
	return instance;
}

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

void EntityManager::update() {
	for(auto& entity : entities) entity.second->update();

}

Entity& EntityManager::create(unsigned int entity_id) {
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


std::vector<EntityId> EntityManager::get_entity_id_list(){
	std::vector<EntityId> ids;
	for(auto &entity:entities){
		ids.push_back(entity.first);
	}
	return ids;
}