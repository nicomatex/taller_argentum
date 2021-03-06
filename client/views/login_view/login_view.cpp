#include "login_view.h"

#include "../../client_config.h"
#include "../../engine/SDL/sdl_timer.h"
#include "../../engine/resource_manager.h"
#include "../../engine/sound_system.h"

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
          ResourceManager::get_instance().get_font(USERNAME_INPUT_FONT_ID), 15),
      login_button(scaler.scale(LOGIN_BUTTON_AREA),
                   scaler.scale(LOGIN_VIEWPORT), window.get_renderer(),
                   game_state_monitor, socket_manager, character_name_input),
      create_character_button(scaler.scale(CREATE_CHAR_BUTTON_AREA),
                              scaler.scale(LOGIN_VIEWPORT),
                              window.get_renderer(), game_state_monitor),
      ui_event_handler(character_name_input, login_button,
                       create_character_button, game_state_monitor) {
    window.set_viewport(scaler.scale(LOGIN_VIEWPORT));
    character_name_input.toggle();  // Activa el cursor del input.
}

LoginView::~LoginView() {}

void LoginView::render_login_alert() {
    switch (game_state_monitor.get_login_state()) {
        case FIRST_LOGIN:
            return;
        case NAME_NOT_FOUND:
            ResourceManager::get_instance()
                .get_texture("interface", ALERT_ID_WRONG_NAME)
                .render(scaler.scale(LOGIN_VIEW_ALERT_AREA));
            break;
        case NAME_ALREADY_CONECTED:
            ResourceManager::get_instance()
                .get_texture("interface", ALERT_ID_ALREADY_ONLINE)
                .render(scaler.scale(LOGIN_VIEW_ALERT_AREA));
            break;
    }
}

void LoginView::run(int fps) {
    int frame_duration = 1000 / fps;
    SDLTimer frame_timer;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    if (!SoundSystem::get_instance().music_playing()) {
        SoundSystem::get_instance().play_music(1);
    }
    while (game_state_monitor.get_game_state() == LOGGING) {
        frame_timer.start();
        window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        background.render(scaler.scale(LOGIN_BACKGROUND_AREA));
        character_name_input.render();
        render_login_alert();
        window.render();

        int frame_time_remaining = frame_duration - frame_timer.get_ticks();
        if (frame_time_remaining > 0) SDL_Delay(frame_time_remaining);
    }
}