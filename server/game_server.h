#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <atomic>

#include "../include/blocking_queue.h"
#include "../include/event.h"
#include "game_loop.h"
#include "th_client_accepter.h"

class GameServer {
   private:
    ServerManager server_manager;
    ThClientAccepter accepter;
    GameLoop game_loop;

    // Esto probablemente no deberia estar aca
    std::atomic_bool running;
    BlockingQueue<Event> event_queue;
    void game_loop();

   public:
    GameServer();

    void run();

    ~GameServer() {}
};

#endif  // GAME_SERVER_H
