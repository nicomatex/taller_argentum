#ifndef TH_DISPATCHER_H
#define TH_DISPATCHER_H

#include <mutex>
#include <unordered_map>

#include "../include/blocking_th_event_handler.h"
#include "../include/event.h"
#include "../include/event_handler.h"

class ThDispatcher : public BlockingThEventHandler {
   private:
    std::mutex m;
    std::unordered_map<int, EventHandler*> handlers;

    void apply_to_threaded(void (BlockingThEventHandler::*func)());

    void stop_handlers();
    void join_handlers();

    void stop_and_join_handlers();

   protected:
    void handle(Event& ev) override;

   public:
    ThDispatcher();
    ~ThDispatcher();

    void stop() override;

    void join() override;
};

#endif  // TH_DISPATCHER_H
