#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include <unordered_map>
#include <vector>

typedef unsigned int EntityId;

class Entity;

class EntityManager {
   private:
    std::unordered_map<EntityId, std::unique_ptr<Entity>> entities;
    EntityManager();

   public:
    static EntityManager& get_instance();
    void update();
    ~EntityManager();
    Entity& create(unsigned int entity_id);
    Entity& get_from_id(unsigned int entity_id);
    bool has_entity(unsigned int entity_id);

    /* Devuelve un vector con los ids de todas las entidades. */
    std::vector<EntityId> get_entity_id_list();
    
    void clean();
};

#endif  // ENTITY_MANAGER_H
