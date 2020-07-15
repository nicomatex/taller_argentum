#include "action_meditate.h"

#include "../entities/player.h"
#include "../map_log_factory.h"

// Temp
#include <iostream>

ActionMeditate::ActionMeditate() {}

void ActionMeditate::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    player->meditate(true);
}
