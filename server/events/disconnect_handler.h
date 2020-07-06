#ifndef DISCONNECT_HANDLER_H
#define DISCONNECT_HANDLER_H

#include "../../include/event.h"
#include "../../include/event_handler.h"

class DisconnectHandler : public EventHandler {
   public:
    DisconnectHandler();

    void push_event(const Event& ev) override;
};

#endif  // DISCONNECT_HANDLER_H
