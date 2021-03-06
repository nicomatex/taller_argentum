#include "action_withdraw_item.h"

#include "../entities/banker.h"
#include "../entities/player.h"

#include <iostream> //Temp

ActionWithdrawItem::ActionWithdrawItem(position_t target, SlotId slot, uint32_t amount)
    : target(target), slot(slot), amount(amount) {}

void ActionWithdrawItem::execute(Map& map, EntityId entity_id) const {
    Banker* banker =
        static_cast<Banker*>(Action::get_entity(map, target));
    if (!banker || banker->get_type() != NPC ||
        banker->get_profession() != BANKER)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    try {
        banker->withdraw_item(slot, amount, player);
    } catch (const OutOfRangeSlotException& e) {
        // lado banker
    } catch (const EmptySlotException& e) {
        // lado banker
    }
    map.push_log(
            MapLogFactory::inventory_change(player->get_name(), player->get_inventory_data())); 
}