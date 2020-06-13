#ifndef TH_DISPATCHER_H
#define TH_DISPATCHER_H

#include "../include/th_event_handler.h"
#include "../nlohmann/json.hpp"

class ThDispatcher : public ThEventHandler {
   private:
    BlockingQueue<Event>& game_queue;

   protected:
    void handle(Event& ev) override;

   public:
    ThDispatcher(BlockingQueue<Event>& queue);

    ~ThDispatcher();
};

#endif  // TH_DISPATCHER_H
