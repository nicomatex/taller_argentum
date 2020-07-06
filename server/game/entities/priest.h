#ifndef PRIEST_H
#define PRIEST_H

#include "npc.h"

class Priest : public Npc {
   public:
    Priest(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Priest();
};

#endif // PRIEST_H