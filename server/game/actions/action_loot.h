#ifndef ACTION_LOOT_H
#define ACTION_LOOT_H

#include "action.h"

class ActionLoot : public Action {
   public:
    ActionLoot();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_LOOT_H
