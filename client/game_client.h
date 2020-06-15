#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <unordered_map>
#include <atomic>

#include "engine/ECS/entity_manager.h"
#include "engine/SDL/sdl_window.h"
#include "engine/entity_factory.h"
#include "../include/socket_manager.h"
#include "receive_handler.h"
#include "../nlohmann/json.hpp"
#include "engine/map.h"
#include "event_factory.h"

/* Interfaz de la clase */
class GameClient {
   private:
    SDLWindow main_window;
    EntityManager entity_manager;
    EntityFactory entitiy_factory;
    std::atomic_bool running;
    void _poll_events();
    Socket socket;
    ClientReceiveHandler receive_handler;
    SocketManager socket_manager;
    Map current_map;
    EventFactory event_factory;

   public:
    GameClient(nlohmann::json config);
    ~GameClient();
    void run();
};

#endif