#ifndef ATTACK_MELEE_HANDLER_H
#define ATTACK_MELEE_HANDLER_H

#include "../../include/event_handler.h"
#include "../../include/types.h"

class AttackHandler : public EventHandler {
   public:
    AttackHandler();

    void push_event(const Event& ev) override;
};

#endif  // ATTACK_MELEE_HANDLER_H
