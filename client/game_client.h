#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <atomic>
#include <unordered_map>

#include "../include/network/socket_manager.h"
#include "../include/nlohmann/json.hpp"
#include "chat_buffer.h"
#include "engine/SDL/sdl_window.h"
#include "engine/map.h"
#include "game_state_monitor.h"
#include "map_change_buffer.h"
#include "network/receive_handler.h"

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

   public:
    GameClient(nlohmann::json config);
    ~GameClient();
    void notify_ready();
    void run();
};

#endif