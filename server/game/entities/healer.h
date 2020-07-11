#ifndef HEALER_H
#define HEALER_H

#include "npc.h"

class Healer : public Npc {
   public:
    Healer(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Healer();
};

#endif // HEALER_H