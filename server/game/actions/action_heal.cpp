#include "action_heal.h"

#include "../entities/healer.h"
#include "../entities/player.h"

ActionHeal::ActionHeal(position_t target) : target(target) {}

void ActionHeal::execute(Map& map, EntityId entity_id) const {
    Healer* healer = static_cast<Healer*>(Action::get_entity(map, target));
    if (!healer || healer->get_type() != NPC ||
        healer->get_profession() != HEALER)
        return;
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    healer->heal(player);
}