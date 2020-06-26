#include "action_melee_atack.h"

void execute(EntityId entity_id, Map& map) const {
    Player& player = static_cast<Player&>(entity);
    player.melee_attack();
}
