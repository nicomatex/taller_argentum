#ifndef CLIENT_DROP_HANDLER_H
#define CLIENT_DROP_HANDLER_H

#include "../../include/blocking_th_event_handler.h"

class ClientDropHandler : public BlockingThEventHandler {
   protected:
    void handle(Event& ev) override;

   public:
    ClientDropHandler();
    ~ClientDropHandler();
};

#endif  // CLIENT_DROP_HANDLER_H
