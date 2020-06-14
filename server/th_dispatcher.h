#ifndef TH_DISPATCHER_H
#define TH_DISPATCHER_H

#include "../include/blocking_th_event_handler.h"

class ThDispatcherHandler : public BlockingThEventHandler {
   protected:
    void handle(Event& ev) override;

   public:
    ThDispatcherHandler();

    ~ThDispatcherHandler();
};

#endif  // TH_DISPATCHER_H
