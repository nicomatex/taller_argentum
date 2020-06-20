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
#include "ui_event_handler.h"
#include "chat.h"

/* Interfaz de la clase */
class GameClient {
   private:
    SDLWindow main_window;
    EntityManager entity_manager;
    EntityFactory entity_factory;
    EventFactory event_factory;
    std::atomic_bool running;
    std::atomic_bool ready;
    Socket socket;
    ClientReceiveHandler receive_handler;
    SocketManager socket_manager;
    Map current_map;
    UiEventHandler ui_event_handler;
    nlohmann::json config;
   public:
    GameClient(nlohmann::json config);
    ~GameClient();
    void run();
};

#endif