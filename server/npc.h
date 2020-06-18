#ifndef NPC_H
#define NPC_H

#include "entity.h"

//TODO: implementar logica

class Npc : public Entity {
   private:
	unsigned int npc_id;
   public:
	Npc();
	~Npc();
	entity_type_t get_type() override;
    void update(unsigned int delta_t) override; // aca ira lógica de pathfinding ?
};

#endif //NPC_H