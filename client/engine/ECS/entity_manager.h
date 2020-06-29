#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

typedef unsigned int EntityId;

class Entity;

class EntityManager {
   private:
    std::unordered_map<EntityId, std::unique_ptr<Entity>> entities;
    std::unordered_map<EntityId, bool> updated;
    std::mutex m;
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

    /* Marca todas las entidades como no actualizadas. */
    void update_initialize();

    /* Remueve las entidades no actualizadas. */
    void remove_non_updated();

    void clean();

    /* Remueve todas las entidades del sistema. */
    void empty();
};

#endif  // ENTITY_MANAGER_H
