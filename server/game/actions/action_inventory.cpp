#include "action_inventory.h"

#include "../entities/entity.h"
#include "../entities/player.h"
#include "../items/item.h"
#include "../map_log_factory.h"

ActionInventory::ActionInventory(SlotId slot) : slot(slot) {}

void ActionInventory::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    player->use(slot);
    map.push_log(MapLogFactory::inventory_change(player->get_name(),
                                                 player->get_inventory_data()));
}
