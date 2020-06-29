#include "entity_manager.h"

#include <iostream>

#include "entity.h"

EntityManager& EntityManager::get_instance() {
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

void EntityManager::update() {
    std::unique_lock<std::mutex> l(m);
    for (auto& entity : entities) entity.second->update();
}

Entity& EntityManager::create(unsigned int entity_id) {
    std::unique_lock<std::mutex> l(m);
    entities[entity_id] = std::unique_ptr<Entity>(new Entity(entity_id));
    updated[entity_id] = true;
    return *entities.at(entity_id);
}

void EntityManager::clean() {
    std::unique_lock<std::mutex> l(m);
    for (auto it = entities.begin(); it != entities.end();) {
        if (!((*it).second->is_alive())) {
            updated.erase((*it).first);
            std::cout << "Borrando para siempre entidad con id " << (*it).first
                      << std::endl;
            it = entities.erase(it);
        } else {
            it++;
        }
    }
}

bool EntityManager::has_entity(unsigned int entity_id) {
    std::unique_lock<std::mutex> l(m);
    return entities.count(entity_id) != 0;
}

Entity& EntityManager::get_from_id(unsigned int entity_id) {
    std::unique_lock<std::mutex> l(m);
    if (entities.count(entity_id) == 0) {
        throw std::exception();
    }
    updated[entity_id] = true;
    return *entities.at(entity_id);
}

std::vector<EntityId> EntityManager::get_entity_id_list() {
    std::unique_lock<std::mutex> l(m);
    std::vector<EntityId> ids;
    for (auto& entity : entities) {
        ids.push_back(entity.first);
    }
    return ids;
}

void EntityManager::update_initialize() {
    std::unique_lock<std::mutex> l(m);
    for (auto& entity : updated) {
        updated[entity.first] = false;
    }
}

void EntityManager::remove_non_updated() {
    std::unique_lock<std::mutex> l(m);
    for (auto& entity : updated) {
        if (entity.second == false) {
            entities.at(entity.first)->kill();
            std::cout << "Removiendo entidad con id " << entity.first
                      << std::endl;
        }
    }
}

void EntityManager::empty() {
    std::unique_lock<std::mutex> l(m);
    entities.erase(entities.begin(), entities.end());
    updated.erase(updated.begin(), updated.end());
}