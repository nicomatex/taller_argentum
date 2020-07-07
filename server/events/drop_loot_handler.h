#ifndef DROP_LOOT_HANDLER_H
#define DROP_LOOT_HANDLER_H

#include "../../include/event_handler.h"

class DropLootHandler : public EventHandler {
   public:
    DropLootHandler();

    void push_event(const Event& ev) override;
};

#endif  // DROP_LOOT_HANDLER_H
