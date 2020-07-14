#include "action_sell.h"

#include "../entities/merchant.h"
#include "../entities/player.h"

#include <iostream>

ActionSell::ActionSell(position_t target, SlotId slot, uint32_t amount)
    : target(target), slot(slot), amount(amount) {}

void ActionSell::execute(Map& map, EntityId entity_id) const {
    Merchant* merchant = static_cast<Merchant*>(Action::get_entity(map, target));
    if (!merchant || merchant->get_type() != NPC || merchant->get_profession() != MERCHANT)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    merchant->sell(slot, amount, player);
    map.push_log(
            MapLogFactory::inventory_change(player->get_name(), player->get_inventory_data())); 
}