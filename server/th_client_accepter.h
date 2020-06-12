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
    SessionManager& session_manager;

   public:
    ThClientAccepter(Socket listener, SessionManager& session_manager);

    virtual void run() override;

    void stop();

    ~ThClientAccepter();
};

#endif  // TH_CLIENT_ACCEPTER_H
