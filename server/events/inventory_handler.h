#ifndef INVENTORY_HANDLER_H
#define INVENTORY_HANDLER_H

#include "../../include/event.h"
#include "../../include/event_handler.h"
#include "../../include/types.h"

class InventoryHandler : public EventHandler {
   public:
    InventoryHandler();

    void push_event(const Event& ev) override;
};

#endif  // INVENTORY_HANDLER_H
