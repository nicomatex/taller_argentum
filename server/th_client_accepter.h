#ifndef TH_CLIENT_ACCEPTER_H
#define TH_CLIENT_ACCEPTER_H

#include "../include/socket.h"
#include "../include/thread.h"
#include "session.h"

class ThClientAccepter : public Thread {
   private:
    Socket listener;
    bool running;
    int next_free_id;
    Session& session;

   public:
    ThClientAccepter(Socket listener, Session& session);

    virtual void run() override;

    void stop();

    ~ThClientAccepter();
};

#endif  // TH_CLIENT_ACCEPTER_H
