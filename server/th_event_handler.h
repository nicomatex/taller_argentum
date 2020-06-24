#ifndef TH_EVENT_HANDLER_H
#define TH_EVENT_HANDLER_H

#include <atomic>
#include <iostream>

#include "../include/event.h"
#include "../include/thread.h"

class ThEventHandler : public Thread {
   private:
    std::atomic<bool> running;

   protected:
    Event event;

    virtual void run_handler() = 0;

   public:
    ThEventHandler(Event ev);

    bool is_done();

    virtual void run() override;

    ~ThEventHandler();
};

#endif  // TH_EVENT_HANDLER_H
