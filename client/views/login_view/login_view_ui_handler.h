#ifndef __LOGIN_UI_EVENT_HANDLER
#define __LOGIN_UI_EVENT_HANDLER

#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "create_character_button.h"
#include "login_button.h"

class LoginUiEventHandler {
   private:
    TextInput& character_name_input;
    GameStateMonitor& game_state_monitor;
    LoginButton& login_button;
    CreateCharacterButton& create_character_button;
    
   public:
    LoginUiEventHandler(TextInput& character_name_input,
                        LoginButton& login_button,
                        CreateCharacterButton& create_character_button,
                        GameStateMonitor& game_state_monitor);
    ~LoginUiEventHandler();
    void handle();
};

#endif