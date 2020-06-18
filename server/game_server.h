#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "server_manager.h"

class GameServer {
   private:
    ServerManager& server_manager;

   public:
    GameServer();

    void run();

    ~GameServer() {}
};

#endif  // GAME_SERVER_H
