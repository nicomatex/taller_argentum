#ifndef ACTION_DEPOSIT_ITEM_H
#define ACTION_DEPOSIT_ITEM_H

#include "action.h"

class ActionDepositItem : public Action {
   private:
    position_t target;
    const SlotId slot;
    const uint32_t amount;

   public:
    ActionDepositItem(position_t target, SlotId slot, uint32_t amount);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_DEPOSIT_ITEM_H
