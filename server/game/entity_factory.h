#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../../include/types.h"
#include "mob_factory.h"

class Player;
class Map;

class EntityFactory {
   private:
    Map& map;
    // Devuelve el siguiente id a asignar a una nueva entidad.
    EntityId get_next_id();

   public:
    EntityFactory(Map& map);
    ~EntityFactory();

    Player* create_player(nlohmann::json player_info);
    Monster* create_monster(MobId monster_id);
    Npc* create_npc(MobId npc_id);
};

#endif  // ENTITY_FACTORY_H
