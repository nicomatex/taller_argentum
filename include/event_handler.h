#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "event.h"

class EventHandler {
   public:
    virtual ~EventHandler() {}

    virtual bool is_threaded() const {
        return false;
    }

    virtual void push_event(const Event& event) = 0;
};

#endif  // EVENT_HANDLER_H
