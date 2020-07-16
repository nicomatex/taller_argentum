#include "healer.h"

#include <iostream>  //Temp

Healer::Healer(EntityId entity_id, nlohmann::json npc_info, Map& map)
    : Npc(entity_id, npc_info, map) {}

Healer::~Healer() {}

void Healer::heal(Player* player) {
    if (!player->is_alive())
        return;
    player->regen_max();
}

void Healer::resuscitate(Player* player) {
    if (player->is_alive())
        return;
    int x_diff = get_map().get_position(id).x -
                 player->get_map().get_position(player->get_id()).x;
    int y_diff = get_map().get_position(id).y -
                 player->get_map().get_position(player->get_id()).y;
    int milliseconds =
        (std::sqrt(x_diff * x_diff + y_diff * y_diff) / 3) * 1000;
    player->immobilize(milliseconds);
    player->teleport(get_map().get_position(id), milliseconds);
    player->resuscitate(milliseconds);
}
