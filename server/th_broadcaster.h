#ifndef SEND_HANDLER_H
#define SEND_HANDLER_H

#include "../include/th_event_handler.h"
#include "clients_monitor.h"

class ThBroadcaster : public ThEventHandler {
   private:
    ClientsMonitor& clients;

   protected:
    virtual void handle(Event& ev) override;

   public:
    ThBroadcaster(ClientsMonitor& clients);

    ~ThBroadcaster();
};

#endif  // SEND_HANDLER_H
