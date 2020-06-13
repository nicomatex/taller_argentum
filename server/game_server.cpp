#include "game_server.h"

#include <iostream>
#include <string>
#include <thread>

#include "../nlohmann/json.hpp"

using json = nlohmann::json;

GameServer::GameServer()
    : session(map, event_queue), accepter(Socket("8080", 10), session) {}

#define TIME_STEP 15

void GameServer::game_loop() {
    std::cerr << "Launching event_loop thread\n";
    while (running) {
        json event = event_queue.pop().get_json();  // TODO: Implementar los event handlers que hacen esto de verdad.
        std::string orientation = event["orientation"];
        if (orientation == "up") {
            map.move(1, {0,-1});
        } else if (orientation == "down") {
            map.move(1, {0,1});
        } else if (orientation == "right") {
            map.move(1, {1,0});
        } else if (orientation == "left") {
            map.move(1, {-1,0});
        }
        std::cout << "Jugador en " << map.get_position_map()[1].x << " - "
                  << map.get_position_map()[1].y << std::endl;
        // sleep (timestep - runtime de esta iteracion)
    }
    //Este game loop no va aca, es solo de prueba.
}

void GameServer::run() {
    accepter.start();
    session.start();
    running = true;
    map.add_entity(1, {5, 5});
    std::thread loop_thread(&GameServer::game_loop, this);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q" || line == "quit")
            break;
        running = false;
    }
    loop_thread.join();
    accepter.stop();
    session.stop();
    session.join();
    accepter.join();
}