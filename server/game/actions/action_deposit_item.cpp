#include "action_deposit_item.h"

#include "../entities/banker.h"
#include "../entities/player.h"

#include <iostream>

ActionDepositItem::ActionDepositItem(position_t target, SlotId slot, uint32_t amount)
    : target(target), slot(slot), amount(amount) {}

void ActionDepositItem::execute(Map& map, EntityId entity_id) const {
    Banker* banker = static_cast<Banker*>(Action::get_entity(map, target));
    if (!banker || banker->get_type() != NPC || banker->get_profession() != BANKER)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    banker->deposit_item(slot, amount, player);
    std::cout << "deposite item" << std::endl;
}