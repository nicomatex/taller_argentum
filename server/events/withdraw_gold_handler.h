#ifndef WITHDRAW_GOLD_HANDLER_H
#define WITHDRAW_GOLD_HANDLER_H

#include "../../include/event_handler.h"

class WithdrawGoldHandler : public EventHandler {
   public:
    WithdrawGoldHandler();

    void push_event(const Event& ev) override;
};

#endif  // WITHDRAW_GOLD_HANDLER_H
