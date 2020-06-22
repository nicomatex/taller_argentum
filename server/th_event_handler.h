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
    ThEventHandler(Event ev) : Thread(), running(false), event(ev) {}

    bool is_done() {
        return running;
    }

    virtual void run() override {
        try {
            running = true;
            run_handler();
        } catch (const std::exception& e) {
            std::cerr << "EventHandler: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "EventHandler: Unknown exception" << std::endl;
        }
        running = false;
    }

    ~ThEventHandler() {}
};

#endif  // TH_EVENT_HANDLER_H
