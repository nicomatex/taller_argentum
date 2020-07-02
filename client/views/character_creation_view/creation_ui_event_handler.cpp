#include "creation_ui_event_handler.h"

CreationUiEventHandler::CreationUiEventHandler(
    TextInput& character_name_input,
    RaceAndClassSelector& race_and_class_selector,
    GoBackButton& go_back_button,
    RequestCharacterCreationButton& req_char_creation_button,
    GameStateMonitor& game_state_monitor)
    : character_name_input(character_name_input),
      race_and_class_selector(race_and_class_selector),
      go_back_button(go_back_button),
      req_char_creation_button(req_char_creation_button),
      game_state_monitor(game_state_monitor) {
    SDL_StartTextInput();
}

CreationUiEventHandler::~CreationUiEventHandler() {}

void CreationUiEventHandler::handle() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                game_state_monitor.quit();
                break;
            case SDL_TEXTINPUT:
                character_name_input.add_characters(e.text.text);
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    character_name_input.erase();
                }
                break;
        }
        race_and_class_selector.handle_event(e);
        go_back_button.handle_event(e);
        req_char_creation_button.handle_event(e);
    }
}