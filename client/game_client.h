#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <unordered_map>
#include <atomic>

#include "engine/ECS/entity_manager.h"
#include "engine/SDL/sdl_window.h"
#include "engine/entity_factory.h"
#include "../include/socket_manager.h"
#include "engine/receive_handler.h"
#include "../nlohmann/json.hpp"
#include "engine/map.h"

using json = nlohmann::json;

/* Interfaz de la clase */
class GameClient {
   private:
    SDLWindow main_window;
    EntityManager entity_manager;
    EntityFactory entitiy_factory;
    std::atomic_bool running;
    void _poll_events();
    Socket socket;
    ClientHandler receive_handler;
    SocketManager socket_manager;
    Map current_map;

   public:
    GameClient(json config);
    ~GameClient();
    void run();
};

#endif