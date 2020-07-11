#include "healer.h"

Healer::Healer(EntityId entity_id, nlohmann::json npc_info, Map& map) :
        Npc(entity_id, npc_info, map) {}

Healer::~Healer() {}

void Healer::heal(Player* player) {
    if (!player->is_alive())
        return;
    player->regen_max();
}

void Healer::revive(Player* player) {
    if (player->is_alive())
        return;
    player->revive();
}
