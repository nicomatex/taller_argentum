#include "login_view.h"

#include "../client_config.h"
#include "../engine/resource_manager.h"

LoginView::LoginView(SDLWindow &window, ResponsiveScaler &scaler,
                     GameStateMonitor &game_state_monitor,
                     SocketManager &socket_manager)
    : window(window),
      scaler(scaler),
      background(ResourceManager::get_instance().get_texture("interface", 2)),
      game_state_monitor(game_state_monitor),
      character_name_input(
          scaler.scale(USERNAME_INPUT_AREA), window.get_renderer(),
          USERNAME_INPUT_FONT_COLOR, USERNAME_INPUT_BG_COLOR,
          ResourceManager::get_instance().get_font(USERNAME_INPUT_FONT_ID)),
      login_button(scaler.scale(LOGIN_BUTTON_AREA),
                   scaler.scale(LOGIN_VIEWPORT), window.get_renderer(),
                   game_state_monitor, socket_manager, character_name_input),
      ui_event_handler(character_name_input, login_button, game_state_monitor) {
    window.set_viewport(scaler.scale(LOGIN_VIEWPORT));
    character_name_input.toggle();  // Activa el cursor del input.
}

LoginView::~LoginView() {}

void LoginView::run() {
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    ResourceManager::get_instance().get_music(1).play();
    while (game_state_monitor.get_game_state() == LOGGING) {
        SDL_Event e;
        ui_event_handler.handle();
        background.render(scaler.scale(LOGIN_BACKGROUND_AREA));
        character_name_input.render();
        window.render();
    }
}