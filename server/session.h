#ifndef SESSION_H
#define SESSION_H

#include "../include/socket_manager.h"
#include "clients_monitor.h"
#include "map.h"
#include "th_broadcaster.h"
#include "th_dispatcher.h"
#include "th_observer.h"

class Session {
   private:
    ClientsMonitor clients;
    ThBroadcaster broadcaster;
    ThObserver observer;

   public:
    Session(Map& map, BlockingQueue<Event>& queue);

    void start();

    void stop();

    void join();

    void add_client(SocketManager* new_client);

    SocketManager* rm_client(int id);

    void join_finished(bool wait);

    ~Session();
};

#endif  // SESSION_H
