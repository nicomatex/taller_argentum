#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "../include/event.h"
#include "../include/types.h"
#include "th_event_handler.h"

class MovementHandler : public ThEventHandler {
   protected:
    void run_handler() override;

   public:
    MovementHandler(Event ev);
    ~MovementHandler();
};

#endif  // MOVEMENT_HANDLER_H
