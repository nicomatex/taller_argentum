#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "../../include/event.h"
#include "../../include/event_handler.h"

class MovementHandler : public EventHandler {
   public:
    MovementHandler();

    void push_event(const Event& ev) override;
};

#endif  // MOVEMENT_HANDLER_H
