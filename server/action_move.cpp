#include "action_move.h"

#include "player.h"

ActionMove::ActionMove(mov_action_t action, direction_t direction)
    : action(action), direction(direction) {}

ActionMove::~ActionMove() {}

void ActionMove::execute(EntityId entity_id, Map &map) const {
    Player *player = static_cast<Player *>(Action::get_entity(map, entity_id));
    player->set_movement(action, direction);
}
