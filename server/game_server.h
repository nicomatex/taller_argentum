#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <atomic>

#include "../include/blocking_queue.h"
#include "../include/event.h"
#include "map.h"
#include "th_client_accepter.h"

class GameServer {
   private:
    Session session;
    ThClientAccepter accepter;
    Map map;
    std::atomic_bool running;
    BlockingQueue<Event> event_queue;
    // Esto probablemente no deberia estar aca
    void game_loop();

   public:
    GameServer();

    void run();

    ~GameServer() {}
};

#endif  // GAME_SERVER_H
