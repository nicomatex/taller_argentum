#ifndef SESSION_H
#define SESSION_H

#include "../include/event.h"
#include "../include/network/socket_manager.h"
#include "../include/types.h"
#include "map_monitor.h"
#include "network/client_id_set.h"
#include "network/th_broadcaster.h"
#include "th_dispatcher.h"
#include "th_observer.h"

class Session {
   private:
    ClientIdSet clients;
    ThBroadcaster broadcaster;
    ThObserver observer;

   public:
    Session(MapMonitor& map);

    void start();

    void stop();

    void join();

    void add_client(ClientId new_client);

    void rm_client(ClientId id);

    void broadcast(const Event& ev);

    ~Session();
};

#endif  // SESSION_H
