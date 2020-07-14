#include "action_deposit_gold.h"
#include "../entities/banker.h"
#include "../entities/player.h"

ActionDepositGold::ActionDepositGold(position_t target, uint32_t amount)
    : target(target), amount(amount) {}

void ActionDepositGold::execute(Map& map, EntityId entity_id) const {
    Banker* banker = static_cast<Banker*>(Action::get_entity(map, target));
    if (!banker || banker->get_type() != NPC ||
        banker->get_profession() != BANKER)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    banker->deposit_gold(amount, player);
}