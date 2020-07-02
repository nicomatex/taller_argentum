#ifndef __LOGIN_VIEW_H
#define __LOGIN_VIEW_H
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "../responsive_scaler.h"
#include "../../../include/network/socket_manager.h"
#include "login_button.h"
#include "create_character_button.h"
#include "login_view_ui_handler.h"

class LoginView {
   private:
    SDLWindow &window;
    ResponsiveScaler &scaler;
    SDLTexture &background;
    GameStateMonitor &game_state_monitor;
    TextInput character_name_input;
    LoginButton login_button;
    CreateCharacterButton create_character_button;
    LoginUiEventHandler ui_event_handler;

   public:
    LoginView(SDLWindow &window, ResponsiveScaler &scaler,
              GameStateMonitor &game_state_monitor,
              SocketManager &socket_manager);
    ~LoginView();

    void run();
};

#endif