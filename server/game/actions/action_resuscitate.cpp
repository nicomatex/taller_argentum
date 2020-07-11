#include "action_resuscitate.h"

#include "../entities/player.h"
#include "../entities/healer.h"

ActionResucitate::ActionResucitate(position_t target) : target(target) {}

void ActionResucitate::execute(Map& map, EntityId entity_id) const {
    /* TODO
    Healer* npc = static_cast<Healer*>(Action::get_entity(map, target));
    if (!npc && npc->get_profession() != CURE)
        return
    */
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (player->is_alive())
        return;
    // npc->res_player(player) -> adentro hace revive
    player->revive();
}
