#ifndef DEPOSIT_GOLD_HANDLER_H
#define DEPOSIT_GOLD_HANDLER_H

#include "../../include/event_handler.h"

class DepositGoldHandler : public EventHandler {
   public:
    DepositGoldHandler();

    void push_event(const Event& ev) override;
};

#endif  // DEPOSIT_GOLD_HANDLER_H
