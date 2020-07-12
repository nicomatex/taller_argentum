#include "action_drop.h"

#include "../entities/player.h"
#include "../map_log_factory.h"

ActionDrop::ActionDrop(SlotId slot, uint32_t amount)
    : slot(slot), amount(amount) {}

void ActionDrop::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    Item* item = player->remove_item(slot, amount);
    if (!item)
        return;
    map.drop_loot(entity_id, item);
}
