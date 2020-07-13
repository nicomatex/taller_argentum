#ifndef USE_ABILITY_HANDLER_H
#define USE_ABILITY_HANDLER_H

#include "../../include/event_handler.h"

class UseAbilityHandler : public EventHandler {
   public:
    UseAbilityHandler();

    void push_event(const Event& ev) override;
};

#endif  // USE_ABILITY_HANDLER_H
