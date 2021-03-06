#ifndef ACTION_BUY_H
#define ACTION_BUY_H

#include "action.h"

class ActionBuy : public Action {
   private:
    position_t target;
    const SlotId slot;
    const uint32_t amount;

   public:
    ActionBuy(position_t target, SlotId slot, uint32_t amount);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_BUY_H
