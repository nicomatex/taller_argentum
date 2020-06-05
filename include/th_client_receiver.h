#ifndef TH_CLIENT_RECEIVER_H
#define TH_CLIENT_RECEIVER_H

#include "blocking_queue.h"
#include "protocol.h"
#include "receive_handler.h"
#include "socket.h"
#include "thread.h"

class ThClientReceiver : public Thread {
   private:
    Socket& socket;
    Protocol protocol;
    ReceiveHandler<std::string>& receiver;

   public:
    ThClientReceiver(Socket& socket, ReceiveHandler<std::string>& receiver);

    // ThClientReceiver(ThClientReceiver&& other);
    // ThClientReceiver& operator=(ThClientReceiver&& other);

    virtual void run() override;

    ~ThClientReceiver();
};

#endif  // TH_CLIENT_RECEIVER_H
