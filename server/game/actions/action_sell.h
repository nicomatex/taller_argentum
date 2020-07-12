#ifndef ACTION_SELL_H
#define ACTION_SELL_H

#include "action.h"

class ActionSell : public Action {
   private:
    position_t target;
    const SlotId slot;
    const uint32_t amount;

   public:
    ActionSell(position_t target, SlotId slot, uint32_t amount);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_SELL_H
