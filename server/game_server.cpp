#include "game_server.h"

#include <iostream>
#include <string>

GameServer::GameServer() : server_manager(ServerManager::get_instance()) {}

void GameServer::run() {
    server_manager.start();
    std::cerr << "GameServer: SERVER STARTED." << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q" || line == "quit")
            break;
        // Otras entradas para el server
    }

    std::cerr << "GameServer: CLOSING..." << std::endl;
    server_manager.finish();
    std::cerr << "GameServer: SERVER CLOSED." << std::endl;
}