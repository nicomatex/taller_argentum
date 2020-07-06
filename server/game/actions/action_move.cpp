#include "action_move.h"

#include "../entities/player.h"

ActionMove::ActionMove(mov_action_t action, direction_t direction)
    : action(action), direction(direction) {}

ActionMove::~ActionMove() {}

void ActionMove::execute(Map &map, EntityId entity_id) const {
    Player *player = static_cast<Player *>(Action::get_entity(map, entity_id));
    player->set_movement(action, direction);
}
