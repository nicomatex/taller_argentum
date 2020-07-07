#ifndef ACTION_UNEQUIP_H
#define ACTION_UNEQUIP_H

#include "action.h"

class ActionUnequip : public Action {
   public:
    ActionUnequip();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_UNEQUIP_H
