#include "action_sell.h"

#include "../entities/merchant.h"
#include "../entities/player.h"

#include <iostream>

ActionSell::ActionSell(position_t target, SlotId slot, uint32_t amount)
    : target(target), slot(slot), amount(amount) {}

void ActionSell::execute(Map& map, EntityId entity_id) const {
    Merchant* merchant = static_cast<Merchant*>(Action::get_entity(map, target));
    if (!merchant || merchant->get_profession() != MERCHANT)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player)
        return;
    Item *item = nullptr;
    try {
        item = player->remove_item(slot, amount);
        if (!item)
            return;
        Gold *gold = merchant->sell(item, amount);
        player->add_item(gold);
    } catch(const FullItemContainerException& e) { //del lado del merchant
        player->add_item(item);
    }
}