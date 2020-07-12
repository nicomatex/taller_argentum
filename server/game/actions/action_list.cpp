#include "action_list.h"

#include <iostream>

#include "../entities/banker.h"
#include "../entities/merchant.h"
#include "../entities/player.h"
#include "../map_log_factory.h"

ActionList::ActionList(position_t target) : target(target) {}

void ActionList::execute(Map& map, EntityId entity_id) const {
    Npc* npc = static_cast<Npc*>(Action::get_entity(map, target));
    if (!npc || npc->get_type() != NPC)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player)
        return;
    switch (npc->get_profession()) {
        case BANKER:
            // TODO:
            break;
        case MERCHANT: {
            Merchant* merchant = static_cast<Merchant*>(npc);
            map.push_log(MapLogFactory::message(
                player->get_name(), {{"message", merchant->list_sale()},
                                     {"from", npc->get_name()}}));
        }
            break;
        default:
            return;
    }
}
