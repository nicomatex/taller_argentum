#ifndef ACTION_DROP_H
#define ACTION_DROP_H

#include "action.h"

class ActionDrop : public Action {
   private:
    const SlotId slot;
    const uint32_t amount;

   public:
    ActionDrop(SlotId slot, uint32_t amount = 1);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_DROP_H
