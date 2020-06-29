#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <atomic>
#include <unordered_map>

#include "../include/network/socket_manager.h"
#include "../include/nlohmann/json.hpp"
#include "chat.h"
#include "chat_buffer.h"
#include "engine/ECS/entity_manager.h"
#include "engine/SDL/sdl_window.h"
#include "engine/entity_factory.h"
#include "engine/map.h"
#include "event_factory.h"
#include "game_state_monitor.h"
#include "map_change_buffer.h"
#include "receive_handler.h"
#include "ui_event_handler.h"

/* Interfaz de la clase */
class GameClient {
   private:
    SDLWindow window;
    MapChangeBuffer map_change_buffer;
    ChatBuffer chat_buffer;
    ClientReceiveHandler receive_handler;
    SocketManager socket_manager;
    nlohmann::json config;
    GameStateMonitor game_state_monitor;
    void _login();

   public:
    GameClient(nlohmann::json config);
    ~GameClient();
    void notify_ready();
    void run();
};

#endif