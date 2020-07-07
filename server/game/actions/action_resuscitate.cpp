#include "action_resuscitate.h"

#include "../entities/player.h"

ActionResucitate::ActionResucitate(position_t target) : target(target) {}

void ActionResucitate::execute(Map& map, EntityId entity_id) const {
    // TODO: TARGET CHECK
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (player->is_alive())
        return;
    player->revive();
}
