#ifndef TH_CLIENT_SENDER_H
#define TH_CLIENT_SENDER_H

#include <functional>

#include "../blocking_th_event_handler.h"
#include "protocol.h"
#include "socket.h"

class ThSocketSender : public BlockingThEventHandler {
   private:
    Protocol protocol;

   protected:
    virtual void handle(Event& ev) override;

   public:
    ThSocketSender(Socket& socket);

    ThSocketSender(ThSocketSender&& other);
    ThSocketSender& operator=(ThSocketSender&& other);
};

#endif  // TH_CLIENT_SENDER_H
