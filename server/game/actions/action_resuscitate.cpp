#include "action_resuscitate.h"

#include "../entities/healer.h"
#include "../entities/player.h"

ActionResucitate::ActionResucitate(position_t target) : target(target) {}

void ActionResucitate::execute(Map& map, EntityId entity_id) const {
    /* TODO
    Healer* npc = static_cast<Healer*>(Action::get_entity(map, target));
    if (!npc && npc->get_profession() != CURE)
        return
    */
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || player->is_alive())
        return;
    // npc->res_player(player) -> adentro hace revive
    player->revive();
}
