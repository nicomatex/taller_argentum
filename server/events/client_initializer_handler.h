#ifndef CLIENT_INITIALIZER_H
#define CLIENT_INITIALIZER_H

#include "../../include/blocking_th_event_handler.h"
#include "../../include/event.h"

class ClientInitializeHandler : public BlockingThEventHandler {
   protected:
    void handle(Event& ev) override;

   public:
    ClientInitializeHandler();
};

#endif  // CLIENT_INITIALIZER_H
