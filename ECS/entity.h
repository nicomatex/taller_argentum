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
    bool isAlive();
    void kill();

    template <class T>
    bool hasComponent() const {
        return components.count(ComponentUtil::getTypeId<T>());
    }

    template <class T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        //Se puede tener una sola vez el componente
        if (hasComponent<T>()) throw std::exception();
        T* component(new T(std::forward<TArgs>(mArgs)...)); //perfect forward
        component->setEntity(this);
        ComponentId c_id = ComponentUtil::getTypeId<T>(); 
        components[c_id] = std::unique_ptr<Component>(component);
        component->init();
        return *component;
    }

    template <class T>
    void delComponent() {
        //No puedo eliminar un componente que no tengo
        if (!hasComponent<T>()) throw std::exception();
        ComponentId c_id = ComponentUtil::getTypeId<T>();
        components[c_id].reset();
        components.erase(c_id);
    }

    template <class T>
    T& getComponent() const {
        if (!hasComponent<T>()) throw std::exception(); 
        ComponentId c_id = ComponentUtil::getTypeId<T>();
        Component *comp = components.at(c_id);
        return *reinterpret_cast<T*>(comp);
    }
};

#endif // ENTITY_H
