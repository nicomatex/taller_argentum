#include "game_server.h"

#include <iostream>
#include <string>

GameServer::GameServer() : server_manager(ServerManager::get_instance()) {}

void GameServer::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q" || line == "quit")
            break;
        // Otras entradas para el server
    }

    std::cerr << "Closing server...\n";
    server_manager.finish();
    std::cerr << "Closed successfully\n";
}