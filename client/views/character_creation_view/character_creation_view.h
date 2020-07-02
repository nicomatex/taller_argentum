#ifndef __CHARACTER_CREATION_VIEW
#define __CHARACTER_CREATION_VIEW

#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "../responsive_scaler.h"
#include "../../../include/network/socket_manager.h"
#include "race_and_class_selector.h"
#include "creation_ui_event_handler.h"
#include "go_back_button.h"
#include "request_char_creation_button.h"

class CharacterCreationView {
   private:
    SDLWindow &window;
    ResponsiveScaler &scaler;
    SDLTexture &background;
    GameStateMonitor &game_state_monitor;
    TextInput character_name_input;
    RaceAndClassSelector race_and_class_selector;
    GoBackButton go_back_button;
    CreationUiEventHandler ui_event_handler;
    RequestCharacterCreationButton req_char_creation_button;
    
    void render_selected_race_info();
    void render_selected_class_info();

   public:
    CharacterCreationView(SDLWindow &window, ResponsiveScaler &scaler,
                          GameStateMonitor &game_state_monitor,
                          SocketManager &socket_manager);
    ~CharacterCreationView();

    void run();
};

#endif