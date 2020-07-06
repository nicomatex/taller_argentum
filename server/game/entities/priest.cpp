#include "priest.h"

Priest::Priest(EntityId entity_id, nlohmann::json npc_info, Map& map) :
        Npc(entity_id, npc_info, map) {}

Priest::~Priest() {}