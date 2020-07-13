#include "action_use_ability.h"

#include "../entities/player.h"

ActionUseAbility::ActionUseAbility(position_t target) : target(target) {}

void ActionUseAbility::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || !player->is_alive())
        return;
    Entity* targeted = Action::get_entity(map, target);
    if (!targeted)
        return;
    player->use_ability(targeted);
}
