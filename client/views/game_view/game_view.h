#ifndef __MAIN_GAME_WINDOW_H
#define __MAIN_GAME_WINDOW_H
#include <atomic>

#include "../../../include/network/socket_manager.h"
#include "../../../include/nlohmann/json.hpp"
#include "../../chat_buffer.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/camera.h"
#include "../../engine/map.h"
#include "../../game_state_monitor.h"
#include "hud.h"
#include "../responsive_scaler.h"
#include "ui_event_handler.h"


class GameView {
   private:
    ResponsiveScaler &scaler;
    SDLWindow &window;
    ChatBuffer &chat_buffer;
    GameStateMonitor &game_state_monitor;
    Hud hud;
    Camera camera;
    UiEventHandler ui_event_handler;
    Map map;

   public:
    GameView(ResponsiveScaler &scaler, int follow_entity_id,
             SocketManager &socket_manager, SDLWindow &window,
             ChatBuffer &chat_buffer, GameStateMonitor &game_state_monitor,
             nlohmann::json map_info);

    void run();

    ~GameView();
};

#endif