#ifndef TH_DISPATCHER_H
#define TH_DISPATCHER_H

#include "../include/blocking_th_event_handler.h"

class ThDispatcher : public BlockingThEventHandler {
   protected:
    void handle(Event& ev) override;

   public:
    ThDispatcher();

    ~ThDispatcher();
};

#endif  // TH_DISPATCHER_H
