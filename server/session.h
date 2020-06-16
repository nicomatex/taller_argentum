#ifndef SESSION_H
#define SESSION_H

#include "../include/socket_manager.h"
#include "client_id_set.h"
#include "map.h"
#include "th_broadcaster.h"
#include "th_dispatcher.h"
#include "th_observer.h"

class Session {
   private:
    ClientIdSet clients;
    ThBroadcaster broadcaster;
    ThObserver observer;

   public:
    Session(Map& map);

    void start();

    void stop();

    void join();

    void add_client(int new_client);

    void rm_client(int id);

    ~Session();
};

#endif  // SESSION_H
