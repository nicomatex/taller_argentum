#ifndef BUY_HANDLER_H
#define BUY_HANDLER_H

#include "../../include/event_handler.h"

class BuyHandler : public EventHandler {
   public:
    BuyHandler();

    void push_event(const Event& ev) override;
};

#endif  // BUY_HANDLER_H
