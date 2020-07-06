#include "action_inventory.h"

#include "../entities/entity.h"
#include "../entities/player.h"
#include "../items/item.h"
#include "../map_log_factory.h"

ActionInventory::ActionInventory(SlotId slot) : slot(slot) {}
ActionInventory::~ActionInventory() {}

void ActionInventory::execute(Map& map, EntityId entity_id) const {
    Entity* entity = Action::get_entity(map, entity_id);
    if (entity->get_type() != PLAYER || !entity->is_alive())
        return;
    Player* player = static_cast<Player*>(entity);

    player->use(slot);
    map.push_log(MapLogFactory::inventory_change(
        player->get_name(), {{"inventory", player->get_inventory_data()}}));
}
