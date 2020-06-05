#ifndef TH_CLIENT_SENDER_H
#define TH_CLIENT_SENDER_H

#include "blocking_queue.h"
#include "protocol.h"
#include "socket.h"
#include "thread.h"

class ThClientSender : public Thread {
   private:
    Socket& socket;
    Protocol protocol;
    BlockingQueue<std::string>& input_queue;

   public:
    ThClientSender(Socket& socket, BlockingQueue<std::string>& queue);

    // ThClientSender(ThClientSender&& other);
    // ThClientSender& operator=(ThClientSender&& other);

    virtual void run() override;

    ~ThClientSender();
};

#endif  // TH_CLIENT_SENDER_H
