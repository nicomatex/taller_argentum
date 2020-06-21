#ifndef CLIENT_INITIALIZER_H
#define CLIENT_INITIALIZER_H

#include "../include/event.h"
#include "th_event_handler.h"

class ClientInitializeHandler : public ThEventHandler {
   protected:
    void run_handler() override;

   public:
    ClientInitializeHandler(Event ev);
    ~ClientInitializeHandler();
};

#endif  // CLIENT_INITIALIZER_H
