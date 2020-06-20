#ifndef __MAIN_GAME_WINDOW_H
#define __MAIN_GAME_WINDOW_H
#include "engine/SDL/sdl_window.h"
#include "engine/camera.h"
#include "engine/map.h"
#include "ui_event_handler.h"
#include "../include/socket_manager.h"
#include "../nlohmann/json.hpp"
#include <atomic>

class Game {
   private:
    UiEventHandler ui_event_handler;
    Map map;
    Camera camera;
    SDLWindow &window;
    std::atomic_bool running;
   public:
    Game(int follow_entity_id,SocketManager &socket_manager, SDLWindow &window);
    void setup_map(nlohmann::json map_info);
    
    void run();

    ~Game();
};

#endif