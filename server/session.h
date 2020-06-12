#ifndef SESSION_H
#define SESSION_H

#include "../include/socket_manager.h"
#include "clients_monitor.h"
#include "th_broadcaster.h"
#include "th_dispatcher.h"

class Session {
   private:
    ClientsMonitor clients;
    ThBroadcaster broadcaster;
    ThDispatcher dispatcher;

   public:
    Session();

    void start();

    void stop();

    void join();

    void add_client(SocketManager* new_client);

    SocketManager* rm_client(int id);

    void join_finished(bool wait);

    ~Session();
};

#endif  // SESSION_H
