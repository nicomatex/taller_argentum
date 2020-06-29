#ifndef ATTACK_MELEE_HANDLER_H
#define ATTACK_MELEE_HANDLER_H

#include "../../include/types.h"
#include "th_event_handler.h"

class AttackHandler : public ThEventHandler {
   private:
    ClientId client_id;

   protected:
    void run_handler() override;

   public:
    AttackHandler(Event& ev);
    ~AttackHandler();
};

#endif  // ATTACK_MELEE_HANDLER_H
