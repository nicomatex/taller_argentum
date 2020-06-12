#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "session_manager.h"
#include "th_client_accepter.h"

class GameServer {
   private:
    SessionManager session_manager;
    ThClientAccepter accepter;

   public:
    GameServer() : accepter(Socket("2500", 10), session_manager) {}

    void run() {
        accepter.start();

        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "q" || line == "quit")
                break;
            // Podemos tener comandos para el server acá
        }
        accepter.stop();
        accepter.join();
    }

    ~GameServer() {}
};

#endif  // GAME_SERVER_H
