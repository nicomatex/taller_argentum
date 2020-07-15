#ifndef ACTION_MEDITATE_H
#define ACTION_MEDITATE_H

#include "action.h"

class ActionMeditate : public Action {
   public:
    ActionMeditate();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_MEDITATE_H
