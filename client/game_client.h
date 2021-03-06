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
#include "inventory_buffer.h"
#include "map_decorations_buffer.h"
#include "player_info_monitor.h"

/**
 * @brief Clase principal del programa.
 * 
 */
class GameClient {
   private:
    SDLWindow window;
    SocketManager socket_manager;
    nlohmann::json config;
    ClientReceiveHandler receive_handler;
    MapChangeBuffer map_change_buffer;
    ChatBuffer chat_buffer;
    InventoryBuffer inventory_buffer;
    MapDecorationsBuffer map_decorations_buffer;
    PlayerInfoMonitor player_info_monitor;
    GameStateMonitor game_state_monitor;

   public:
    GameClient(nlohmann::json config);
    ~GameClient();
    void notify_ready();
    void run();
};

#endif