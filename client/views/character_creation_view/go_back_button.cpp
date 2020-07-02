#include "go_back_button.h"
#include "../../engine/resource_manager.h"

GoBackButton::GoBackButton(SDL_Rect button_area, SDL_Rect viewport,
                           SDL_Renderer* renderer,
                           GameStateMonitor& game_state_monitor)
    : Button(button_area, viewport, renderer),
      game_state_monitor(game_state_monitor) {}


void GoBackButton::on_click(){
    ResourceManager::get_instance().get_sound_fx(3).play();
    game_state_monitor.set_game_state(LOGGING);
}