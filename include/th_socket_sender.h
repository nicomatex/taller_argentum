#ifndef TH_CLIENT_SENDER_H
#define TH_CLIENT_SENDER_H

#include <functional>

#include "protocol.h"
#include "socket.h"
#include "th_event_handler.h"

class ThSocketSender : public ThEventHandler {
   private:
    Protocol protocol;

   protected:
    virtual void handle(Command& ev) override;

   public:
    ThSocketSender(Socket& socket);

    ThSocketSender(ThSocketSender&& other);
    ThSocketSender& operator=(ThSocketSender&& other);

    ~ThSocketSender();
};

#endif  // TH_CLIENT_SENDER_H
