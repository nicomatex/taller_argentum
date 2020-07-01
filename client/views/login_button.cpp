#include "login_button.h"
#include "../engine/resource_manager.h"
#include "../network/event_factory.h"

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
    game_state_monitor.set_game_state(WAITING_FOR_INITIALIZATION);
    socket_manager.send(EventFactory::connect_event(name,"123"));
    ResourceManager::get_instance().get_sound_fx(3).play();
}