#ifndef HEAL_HANDLER_H
#define HEAL_HANDLER_H

#include "../../include/event_handler.h"

class HealHandler : public EventHandler {
   public:
    HealHandler();

    void push_event(const Event& ev) override;
};

#endif  // HEAL_HANDLER_H
