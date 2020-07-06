#include "action_loot.h"

#include "../entities/player.h"
#include "../map_log_factory.h"

ActionLoot::ActionLoot() {}

void ActionLoot::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    Item* item = map.pickup_loot(player->get_id());
    if (!item)
        return;
    try {
        player->add_item(item);
        map.push_log(MapLogFactory::inventory_change(
            player->get_name(), player->get_inventory_data()));
    } catch (const FullItemContainerException& e) {
        map.drop_loot(player->get_id(), item);
        map.push_log(MapLogFactory::inventory_full(player->get_name()));
    }
}
