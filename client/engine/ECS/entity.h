#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "../../../include/my_exception.h"
#include "component.h"
#include "component_util.h"
#include "entity_manager.h"

/**
 * @brief Entidad (NPCs y personajes)
 *
 */
class Entity {
   private:
    unsigned int id;
    bool alive;
    std::unordered_map<ComponentId, std::unique_ptr<Component>> components;

   public:
    Entity(unsigned int id);
    ~Entity();

    /**
     * @brief Actualiza cada uno de los componentes de la entidad.
     *
     */
    void update();

    /**
     * @brief Indica si la entidad continuara activa luego del ultimo clean.
     *
     * @return true si continuara activa.
     * @return false si no continuara activa.
     */
    bool is_alive();

    /**
     * @brief Indica que la entidad debe ser limpiada en el proximo clean.
     *
     */
    void kill();

    template <class T>
    bool has_component() const {
        return components.count(ComponentUtil::get_type_id<T>());
    }

    /**
     * @brief Agrega una componente a la entidad.
     *
     * @tparam T Clase del componente a agregar.
     * @tparam TArgs Argumentos del constructor de la componente.
     * @param mArgs
     * @return T&
     */
    template <class T, typename... TArgs>
    T& add_component(TArgs&&... mArgs) {
        // Se puede tener una sola vez el componente
        if (has_component<T>())
            throw MyException("Entity: already has that component");
        T* component(new T(std::forward<TArgs>(mArgs)...));  // perfect forward
        component->set_entity(this);
        ComponentId c_id = ComponentUtil::get_type_id<T>();
        components[c_id] = std::unique_ptr<Component>(component);
        component->init();
        return *component;
    }

    /**
     * @brief Borra una componente de la entidad.
     *
     * @tparam T Clase de la componente a borrar.
     */
    template <class T>
    void del_component() {
        // No puedo eliminar un componente que no tengo
        if (!has_component<T>())
            throw MyException("Entity: cannot delete an unexistent component");
        ComponentId c_id = ComponentUtil::get_type_id<T>();
        components[c_id].reset();
        components.erase(c_id);
    }

    /**
     * @brief Devuelve una componente.
     *
     * @tparam T Clase de la componente que se desea obtener.
     * @return T& Componente.
     */
    template <class T>
    T& get_component() const {
        if (!has_component<T>())
            throw MyException("Entity: cannot get an unexistent component");
        ComponentId c_id = ComponentUtil::get_type_id<T>();
        Component* comp = components.at(c_id).get();
        return *reinterpret_cast<T*>(comp);
    }
};

#endif  // ENTITY_H
