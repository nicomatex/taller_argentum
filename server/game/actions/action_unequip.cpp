#include "action_unequip.h"

#include "../entities/player.h"

ActionUnequip::ActionUnequip(SlotId slot) : slot(slot) {}

void ActionUnequip::execute(Map& map, EntityId entity_id) const {
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    player->unequip(slot);
}
