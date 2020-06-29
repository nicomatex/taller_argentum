#ifndef SEND_HANDLER_H
#define SEND_HANDLER_H

#include "../../include/blocking_th_event_handler.h"
#include "client_id_set.h"

class ThBroadcaster : public BlockingThEventHandler {
   private:
    ClientIdSet& clients;

   protected:
    virtual void handle(Event& ev) override;

   public:
    ThBroadcaster(ClientIdSet& clients);

    ~ThBroadcaster();
};

#endif  // SEND_HANDLER_H
