#ifndef TH_EVENT_HANDLER_H
#define TH_EVENT_HANDLER_H

#include <stdexcept>

#include "blocking_queue.h"
#include "command.h"
#include "thread.h"

class EventHandlerStoppedException : public std::exception {
   public:
    EventHandlerStoppedException() {}

    virtual const char* what() const noexcept override {
        return "The Event Handler has been stopped";
    }

    ~EventHandlerStoppedException() {}
};

class ThEventHandler : public Thread {
   private:
    BlockingQueue<Command> event_queue;

   protected:
    Command pop_event();

    virtual void handle(Command& ev) = 0;

   public:
    ThEventHandler();

    ThEventHandler(ThEventHandler&& other);
    ThEventHandler& operator=(ThEventHandler&& other);

    void push_event(const Command& ev);

    virtual void run() override;

    void stop();

    ~ThEventHandler();
};

#endif  // TH_EVENT_HANDLER_H
