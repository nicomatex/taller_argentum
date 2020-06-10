#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "../include/socket_manager.h"
#include "../test_client_server/str_receive_server_handler.h"
#include "clients_monitor.h"
#include "th_broadcaster.h"

class Session {
   private:
    ClientsMonitor clients;
    ThBroadcaster broadcaster;
    StrReceiveServerHandler recv_handler;

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

#endif  // SESSION_MANAGER_H
