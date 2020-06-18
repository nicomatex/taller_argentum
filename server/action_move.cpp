#include "action_move.h"
#include "player.h"

ActionMove::ActionMove(int new_speed_x, int new_speed_y)
    : new_speed_x(new_speed_x), new_speed_y(new_speed_y) {}

ActionMove::~ActionMove(){}

void ActionMove::execute(Entity &entity) const{
    Player &player = static_cast<Player&>(entity);
    player.set_current_speed(new_speed_x,new_speed_y);
}