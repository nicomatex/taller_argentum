#ifndef ACTION_RESUSCITATE_H
#define ACTION_RESUSCITATE_H

#include "action.h"

class ActionResucitate : public Action {
   private:
    position_t target;

   public:
    ActionResucitate(position_t target);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_RESUSCITATE_H
