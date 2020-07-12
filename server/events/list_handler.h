#ifndef LIST_HANDLER_H
#define LIST_HANDLER_H

#include "../../include/event_handler.h"

class ListHandler : public EventHandler {
   public:
    ListHandler();

    void push_event(const Event& ev) override;
};

#endif  // LIST_HANDLER_H
