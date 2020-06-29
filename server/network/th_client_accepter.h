#ifndef TH_CLIENT_ACCEPTER_H
#define TH_CLIENT_ACCEPTER_H

#include "../../include/network/socket.h"
#include "../../include/thread.h"
#include "session.h"

class ThClientAccepter : public Thread {
   private:
    Socket listener;
    bool running;

    ClientId get_next_id();

   public:
    ThClientAccepter(Socket listener);

    virtual void run() override;

    void stop();

    ~ThClientAccepter();
};

#endif  // TH_CLIENT_ACCEPTER_H
