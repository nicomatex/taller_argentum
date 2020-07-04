#ifndef ACTION_MELEE_ATTACK_H
#define ACTION_MELEE_ATTACK_H

#include "action.h"

class ActionAttack : public Action {
   public:
    ActionAttack();
    ~ActionAttack();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_MELEE_ATTACK_H
