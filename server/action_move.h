#ifndef __ACTION_MOVE_H
#define __ACTION_MOVE_H

#include "../include/types.h"
#include "action.h"

class ActionMove : public Action {
    mov_action_t action;
    direction_t direction;

   public:
    ActionMove(mov_action_t action, direction_t direction);
    ~ActionMove();
    void execute(Entity &entity) const override;
};

#endif