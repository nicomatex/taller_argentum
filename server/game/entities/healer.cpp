#include "healer.h"

Healer::Healer(EntityId entity_id, nlohmann::json npc_info, Map& map) :
        Npc(entity_id, npc_info, map) {}

Healer::~Healer() {}