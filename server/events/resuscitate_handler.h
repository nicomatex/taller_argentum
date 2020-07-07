#ifndef RESUSCITATE_HANDLER_H
#define RESUSCITATE_HANDLER_H

#include "../../include/event_handler.h"

class ResuscitateHandler : public EventHandler {
   public:
    ResuscitateHandler();

    void push_event(const Event& ev) override;
};

#endif  // RESUSCITATE_HANDLER_H
