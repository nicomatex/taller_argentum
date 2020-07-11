#ifndef HEALER_H
#define HEALER_H

#include "npc.h"
#include "player.h"

class Healer : public Npc {
   public:
    Healer(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Healer();
    void heal(Player* player);
    void revive(Player* player);
};

#endif // HEALER_H