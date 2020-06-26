#ifndef ATTACK_MELEE_HANDLER_H
#define ATTACK_MELEE_HANDLER_H

#include "th_event_handler.h"

class AttackMeleeHandler : public ThEventHandler {
   protected:
    void run_handler() override;

   public:
    AttackMeleeHandler(ClientId client_id);
    ~AttackMeleeHandler();
};

#endif  // ATTACK_MELEE_HANDLER_H
