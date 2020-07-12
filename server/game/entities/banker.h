#ifndef BANKER_H
#define BANKER_H

#include "npc.h"
#include "player.h"

class Banker : public Npc {
   public:
    Banker(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Banker();
};

#endif // BANKER_H