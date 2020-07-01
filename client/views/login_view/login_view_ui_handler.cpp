#include "login_view_ui_handler.h"

#include "SDL2/SDL.h"
LoginUiEventHandler::LoginUiEventHandler(TextInput& character_name_input,
                                         LoginButton& login_button,
                                         GameStateMonitor& game_state_monitor)
    : character_name_input(character_name_input),
      login_button(login_button),
      game_state_monitor(game_state_monitor) {
    SDL_StartTextInput();
}

LoginUiEventHandler::~LoginUiEventHandler() {}

void LoginUiEventHandler::handle() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_TEXTINPUT) {
            character_name_input.add_characters(e.text.text);
        } else if (e.type == SDL_QUIT) {
            game_state_monitor.quit();
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_BACKSPACE:
                    character_name_input.erase();
                    break;
                case SDLK_RETURN:
                    login_button.on_click();
                    break;
            }
        }
        login_button.handle_event(e);
    }
}
