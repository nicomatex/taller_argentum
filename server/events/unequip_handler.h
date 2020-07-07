#ifndef UNEQUIP_HANDLER_H
#define UNEQUIP_HANDLER_H

#include "../../include/event_handler.h"

class UnequipHandler : public EventHandler {
   public:
    UnequipHandler();

    void push_event(const Event& ev) override;
};

#endif  // UNEQUIP_HANDLER_H
