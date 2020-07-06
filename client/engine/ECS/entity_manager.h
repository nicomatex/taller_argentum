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
   /**
    * @brief Devuelve el EntityManager, que es un singleton.
    * 
    * @return EntityManager& 
    */
    static EntityManager& get_instance();

    /**
     * @brief Actualiza todas las entidades.
     * 
     */
    void update();
    ~EntityManager();

    /**
     * @brief Crea una nueva entidad.
     * 
     * @param entity_id Id con el cual se identificara la entidad creada.
     * @return Entity& 
     */
    Entity& create(unsigned int entity_id);

    /**
     * @brief Devuelve una entidad segun su id.
     * 
     * @param entity_id id de la entidad a obtener.
     * @return Entity& 
     */
    Entity& get_from_id(unsigned int entity_id);

    /**
     * @brief Indica si una entidad existe.
     * 
     * @param entity_id id de la entidad cuya existencia se quiere checkear.
     * @return true si la entidad existe.
     * @return false si la entidad no existe.
     */
    bool has_entity(unsigned int entity_id);

    /**
     * @brief Devuelve un vector con los ids de todas las entidades existentes.
     * 
     * @return std::vector<EntityId> 
     */
    std::vector<EntityId> get_entity_id_list();

    /**
     * @brief Marca todas las entidades como no actualizadas.
     * 
     */
    void update_initialize();

    /**
     * @brief Indica que todas las entidades no actualizadas deben ser quitadas
     * en el proximo clean.
     * 
     */
    void remove_non_updated();

    /**
     * @brief Quita todas las entidades marcadas con alive = false.
     * 
     */
    void clean();

    /**
     * @brief Remueve todas las entidades.
     * 
     */
    void empty();
};

#endif  // ENTITY_MANAGER_H
