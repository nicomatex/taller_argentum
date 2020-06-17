#ifndef __ACTION_MOVE_H
#define __ACTION_MOVE_H

#include "action.h"

class ActionMove: public Action{
    int new_speed_x;
    int new_speed_y;

    public:
        ActionMove(int new_speed_x, int new_speed_y);
        ~ActionMove();
        void execute(Entity &entity) const override;
};

#endif