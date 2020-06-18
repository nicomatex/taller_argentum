#ifndef __ACTION_H
#define __ACTION_H

#include "entity.h"

class Action {
   public:
    virtual ~Action(){};
    virtual void execute(Entity &entity) const = 0;
};

#endif