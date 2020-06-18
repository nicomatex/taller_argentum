#ifndef NPC_H
#define NPC_H

#include "entity.h"

/*	

	Weapon-> special_efect(attacker,attacked)

	Entity debería tener un name, y un sprite						
																								
			Monster : public Fighter				Player: public Fighter            Npc:	
			->monster_id (para json)				-> mana							  ->npc_id (para json)
				                               		-> gold
				                              		-> stats
				                              		-> experience
				                              		-> inventory
				                              		-> equipped_items
													-> etc...
			Interface Fighter													
		health				       < pasar a cada clase		      
		min_damage/max_damage	   <
		bool isAlive;              <
		virtual list<Loot> dropOnDeath();
		virtual bool attack(fighter &fighter); true si lo mate 0 si no
		virtual bool receiveDamage(int damage, id_atacante); true si logro matarme, 0 sino
		____________________________________________________

				En Monster


		bool attack(fighter &fighter) {
			return fighter->receiveDamage(random(MinDamage y MaxDamage))
		}
		
		bool receiveDamage(int daño) {
			if (health - daño <= 0) {
				health = 0;
				isAlive = false;
				return true;
			} else {
				health -= daño;
				return false;
			}		
		}
		____________________________________________________
		Map-> se guarda Monsters y Npcs? SIP

*/

/*
	Preguntas/Pensamientos:
	Todos los monsters dropean lo mismo asi que no tiene sentido hacer una loot tablE


*/

/*
	Probabilidad -> Item dejado
	0.80 Nada
	0.08 Oro, una cantidad igual a rand(0.01, 0.2) * VidaMaxNPC
	0.01 Un poción de vida o mana elegida al azar
	0.01 Cualquier otro objeto al azar

	-  Goblin
	-  Esqueleto
	-  Zombie
	-  Araña

*/


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