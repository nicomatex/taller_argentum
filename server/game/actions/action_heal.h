#ifndef ACTION_HEAL_H
#define ACTION_HEAL_H

#include "action.h"

class ActionHeal : public Action {
   private:
    position_t target;

   public:
    ActionHeal(position_t target);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_HEAL_H
