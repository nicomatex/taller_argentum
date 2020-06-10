#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <unordered_map>

class Entity;

class EntityManager {
   private:
    std::unordered_map<unsigned int, std::unique_ptr<Entity>> entities;
   public:
    void update(int dt);
    void draw();
    EntityManager();
    ~EntityManager();
    Entity& create();
    Entity& get_from_id(unsigned int entity_id);
    bool has_entity(unsigned int entity_id);
    void clean();
};

#endif // ENTITY_MANAGER_H
