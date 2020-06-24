#ifndef TH_DISPATCHER_H
#define TH_DISPATCHER_H

#include <vector>

#include "../include/blocking_th_event_handler.h"
#include "th_event_handler.h"

class ThDispatcher : public BlockingThEventHandler {
   private:
    std::vector<ThEventHandler*> started_set;

    void join_done(bool wait);

   protected:
    void handle(Event& ev) override;

   public:
    ThDispatcher();
    ~ThDispatcher();

    void stop() override;
};

#endif  // TH_DISPATCHER_H
