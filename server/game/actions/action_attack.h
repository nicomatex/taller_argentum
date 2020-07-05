#ifndef ACTION_ATTACK_H
#define ACTION_ATTACK_H

#include "action.h"

class ActionAttack : public Action {
   public:
    ActionAttack();
    ~ActionAttack();

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_ATTACK_H
