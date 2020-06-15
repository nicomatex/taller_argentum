#ifndef CLIENT_INITIALIZER_H
#define CLIENT_INITIALIZER_H

#include "server_manager.h"
#include "th_event_handler.h"

class ClientInitializeHandler : public ThEventHandler {
   private:
    ServerManager& server_manager;

   protected:
    void run_handler() override;
   public:
    ClientInitializeHandler(Event ev, ServerManager& server_manager);
    ~ClientInitializeHandler();
};

#endif  // CLIENT_INITIALIZER_H
