#ifndef __CREATION_UI_EVENT_HANDLER
#define __CREATION_UI_EVENT_HANDLER

#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "go_back_button.h"
#include "race_and_class_selector.h"
#include "request_char_creation_button.h"

class CreationUiEventHandler {
    TextInput& character_name_input;
    GameStateMonitor& game_state_monitor;
    RaceAndClassSelector& race_and_class_selector;
    GoBackButton& go_back_button;
    RequestCharacterCreationButton& req_char_creation_button;

   public:
    CreationUiEventHandler(TextInput& character_name_input,
                           RaceAndClassSelector& race_and_class_selector,
                           GoBackButton& go_back_button,
                           RequestCharacterCreationButton& req_char_creation_button,
                           GameStateMonitor& game_state_monitor);
    ~CreationUiEventHandler();

    void handle();
};

#endif