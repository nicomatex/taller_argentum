#ifndef CLIENT_DROP_HANDLER_H
#define CLIENT_DROP_HANDLER_H

#include "th_event_handler.h"

class ClientDropHandler : public ThEventHandler {
   protected:
    void run_handler() override;

   public:
    ClientDropHandler(Event ev);

    ~ClientDropHandler();
};

#endif  // CLIENT_DROP_HANDLER_H
