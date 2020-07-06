#ifndef PICKUP_LOOT_HANDLER_H
#define PICKUP_LOOT_HANDLER_H

#include "../../include/event.h"
#include "../../include/event_handler.h"

class PickupLootHandler : public EventHandler {
   public:
    PickupLootHandler();

    void push_event(const Event& ev) override;
};

#endif  // PICKUP_LOOT_HANDLER_H
