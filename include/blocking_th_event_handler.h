#ifndef BLOCKING_TH_EVENT_HANDLER_H
#define BLOCKING_TH_EVENT_HANDLER_H

#include <stdexcept>

#include "blocking_queue.h"
#include "event.h"
#include "event_handler.h"
#include "thread.h"

class EventHandlerStoppedException : public std::exception {
   public:
    EventHandlerStoppedException() {}

    virtual const char* what() const noexcept override {
        return "The Event Handler has been stopped";
    }

    ~EventHandlerStoppedException() {}
};

class BlockingThEventHandler : public Thread, public EventHandler {
   private:
    BlockingQueue<Event> event_queue;

   protected:
    Event pop_event();

    virtual void handle(Event& ev) = 0;

   public:
    BlockingThEventHandler();
    virtual ~BlockingThEventHandler();

    BlockingThEventHandler(BlockingThEventHandler&& other);
    BlockingThEventHandler& operator=(BlockingThEventHandler&& other);

    bool is_threaded() const override;

    bool is_done() const;

    void push_event(const Event& ev) override;

    virtual void run() override;

    virtual void stop();
};

#endif  // BLOCKING_TH_EVENT_HANDLER_H
