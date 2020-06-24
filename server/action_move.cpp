#include "action_move.h"

#include "player.h"

ActionMove::ActionMove(mov_action_t action, direction_t direction)
    : action(action), direction(direction) {}

ActionMove::~ActionMove() {}

void ActionMove::execute(Entity &entity) const {
    Player &player = static_cast<Player &>(entity);
    player.set_current_movement(action, direction);
}
