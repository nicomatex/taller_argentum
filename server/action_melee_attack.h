#ifndef ACTION_MELEE_ATTACK_H
#define ACTION_MELEE_ATTACK_H

#include "action.h"
#include "map.h"

class ActionMeleeAttack : public Action {
   public:
    ActionMeleeAttack();
    ~ActionMeleeAttack();

    void execute(EntityId entity_id, Map& map) const override;
};

#endif  // ACTION_MELEE_ATTACK_H
