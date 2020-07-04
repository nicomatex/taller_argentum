#ifndef __CHAR_CREATION_BUTTON_H
#define __CHAR_CREATION_BUTTON_H

#include "../../../include/network/socket_manager.h"
#include "../../engine/UI/button.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "race_and_class_selector.h"

class RequestCharacterCreationButton : public Button {
   private:
    SocketManager& socket_manager;
    TextInput& character_name_input;
    RaceAndClassSelector& race_and_class_selector;
    GameStateMonitor& game_state_monitor;

   public:
    RequestCharacterCreationButton(
        SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
        SocketManager& socket_manager, TextInput& character_name_input,
        RaceAndClassSelector& race_and_class_selector,
        GameStateMonitor& game_state_monitor);

    void on_click() override;
};

#endif