#ifndef ACTION_USE_ABILITY_H
#define ACTION_USE_ABILITY_H

#include "../position.h"
#include "action.h"

class ActionUseAbility : public Action {
   private:
    position_t target;

   public:
    ActionUseAbility(position_t target);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_USE_ABILITY_H
