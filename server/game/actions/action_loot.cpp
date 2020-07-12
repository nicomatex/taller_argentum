#include "action_loot.h"

#include "../entities/player.h"
#include "../map_log_factory.h"

// Temp
#include <iostream>

ActionLoot::ActionLoot() {}

void ActionLoot::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    Item* item = map.pickup_loot(player->get_id());
    if (!item)
        return;
    player->add_item(item);
}
