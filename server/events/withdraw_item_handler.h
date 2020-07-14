#ifndef WITHDRAW_ITEM_HANDLER_H
#define WITHDRAW_ITEM_HANDLER_H

#include "../../include/event_handler.h"

class WithdrawItemHandler : public EventHandler {
   public:
    WithdrawItemHandler();

    void push_event(const Event& ev) override;
};

#endif  // WITHDRAW_ITEM_HANDLER_H
