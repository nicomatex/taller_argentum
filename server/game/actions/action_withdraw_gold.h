#ifndef ACTION_WITHDRAW_GOLD_H
#define ACTION_WITHDRAW_GOLD_H

#include "action.h"

class ActionWithdrawGold : public Action {
   private:
    position_t target;
    const uint32_t amount;

   public:
    ActionWithdrawGold(position_t target, uint32_t amount);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_WITHDRAW_GOLD_H
