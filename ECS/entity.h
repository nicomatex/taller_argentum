#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include <bitset>
#include <exception>
#include <iostream>
#include <unordered_map>
#include "component.h"
#include "component_util.h"
#include "entity_manager.h"

class Entity {
   private:
    unsigned int id;
    bool alive;
    std::unordered_map<ComponentId, std::unique_ptr<Component>> components;
    
   public:
    Entity(unsigned int id);
    ~Entity();
    void update(int dt);
    void draw();
    bool is_alive();
    void kill();

    template <class T>
    bool has_component() const {
        return components.count(ComponentUtil::get_type_id<T>());
    }

    template <class T, typename... TArgs>
    T& add_component(TArgs&&... mArgs) {
        //Se puede tener una sola vez el componente
        if (has_component<T>()) throw std::exception();
        T* component(new T(std::forward<TArgs>(mArgs)...)); //perfect forward
        component->set_entity(this);
        ComponentId c_id = ComponentUtil::get_type_id<T>(); 
        components[c_id] = std::unique_ptr<Component>(component);
        component->init();
        return *component;
    }

    template <class T>
    void del_component() {
        //No puedo eliminar un componente que no tengo
        if (!has_component<T>()) throw std::exception();
        ComponentId c_id = ComponentUtil::get_type_id<T>();
        components[c_id].reset();
        components.erase(c_id);
    }

    template <class T>
    T& get_component() const {
        if (!has_component<T>()) throw std::exception(); 
        ComponentId c_id = ComponentUtil::get_type_id<T>();
        Component *comp = components.at(c_id);
        return *reinterpret_cast<T*>(comp);
    }
};

#endif // ENTITY_H
