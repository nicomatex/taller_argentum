#include "login_button.h"

#include "../../engine/sound_system.h"
#include "../../network/event_factory.h"

LoginButton::LoginButton(SDL_Rect button_area, SDL_Rect viewport,
                         SDL_Renderer* renderer,
                         GameStateMonitor& game_state_monitor,
                         SocketManager& socket_manager,
                         TextInput& character_name_input)
    : Button(button_area, viewport, renderer),
      game_state_monitor(game_state_monitor),
      socket_manager(socket_manager),
      character_name_input(character_name_input) {}

void LoginButton::on_click() {
    std::string name = character_name_input.get_text();
    socket_manager.send(EventFactory::connect_event(name, "123"));
    SoundSystem::get_instance().play_ui_sfx(3);
}