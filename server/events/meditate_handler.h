#ifndef MEDITATE_HANDLER_H
#define MEDITATE_HANDLER_H

#include "../../include/event.h"
#include "../../include/event_handler.h"

class MeditateHandler : public EventHandler {
   public:
    MeditateHandler();

    void push_event(const Event& ev) override;
};

#endif  // MEDITATE_HANDLER_H
