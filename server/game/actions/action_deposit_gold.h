#ifndef ACTION_DEPOSIT_GOLD_H
#define ACTION_DEPOSIT_GOLD_H

#include "action.h"

class ActionDepositGold : public Action {
   private:
    position_t target;
    const uint32_t amount;

   public:
    ActionDepositGold(position_t target, uint32_t amount);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_DEPOSIT_GOLD_H
