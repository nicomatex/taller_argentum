#ifndef __CHARACTER_CREATION_VIEW
#define __CHARACTER_CREATION_VIEW

#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "../responsive_scaler.h"
#include "../../../include/network/socket_manager.h"

class CharacterCreationView {
   private:
    SDLWindow &window;
    ResponsiveScaler &scaler;
    SDLTexture &background;
    GameStateMonitor &game_state_monitor;

   public:
    CharacterCreationView(SDLWindow &window, ResponsiveScaler &scaler,
                          GameStateMonitor &game_state_monitor,
                          SocketManager &socket_manager);
    ~CharacterCreationView();

    void run();
};

#endif