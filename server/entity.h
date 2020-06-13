#ifndef __ENTITY_H
#define __ENTITY_H

enum entity_type_t { PLAYER, NPC, LOOT };

class Entity {
   protected:
    unsigned int id;

   public:
    Entity(unsigned int id);
    virtual ~Entity();

    /* Saber el tipo de la entidad sirve para saber si es colisionable o no.
    Los players y npcs son colisionables; el loot no.*/
    virtual entity_type_t get_type() = 0;
    
    virtual void update(unsigned int delta_t);
    unsigned int get_id() const;
};

#endif