#ifndef ACTION_RESUSCITATE_H
#define ACTION_RESUSCITATE_H

#include "action.h"

class ActionResuscitate : public Action {
   public:
    ActionResuscitate();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_RESUSCITATE_H
