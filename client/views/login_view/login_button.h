#ifndef __LOGIN_BUTTON_H
#define __LOGIN_BUTTON_H
#include "../../../include/network/socket_manager.h"
#include "../../engine/UI/button.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"

class LoginButton : public Button {
    GameStateMonitor& game_state_monitor;
    SocketManager& socket_manager;
    TextInput& character_name_input;

   public:
    LoginButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
                GameStateMonitor& game_state_monitor,
                SocketManager& socket_manager,
                TextInput& character_name_input);
    void on_click() override;
};

#endif