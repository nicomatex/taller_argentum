#ifndef ACTION_LIST_H
#define ACTION_LIST_H

#include "action.h"

class ActionList : public Action {
   private:
    position_t target;

   public:
    ActionList(position_t target);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_LIST_H
