#ifndef DEPOSIT_ITEM_HANDLER_H
#define DEPOSIT_ITEM_HANDLER_H

#include "../../include/event_handler.h"

class DepositItemHandler : public EventHandler {
   public:
    DepositItemHandler();

    void push_event(const Event& ev) override;
};

#endif  // DEPOSIT_ITEM_HANDLER_H
