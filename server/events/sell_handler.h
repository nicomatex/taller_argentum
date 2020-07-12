#ifndef SELL_HANDLER_H
#define SELL_HANDLER_H

#include "../../include/event_handler.h"

class SellHandler : public EventHandler {
   public:
    SellHandler();

    void push_event(const Event& ev) override;
};

#endif  // SELL_HANDLER_H
