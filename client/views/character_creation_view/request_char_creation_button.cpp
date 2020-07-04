#include "request_char_creation_button.h"

#include "../../engine/resource_manager.h"
#include "../../network/event_factory.h"

RequestCharacterCreationButton::RequestCharacterCreationButton(
    SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
    SocketManager& socket_manager, TextInput& character_name_input,
    RaceAndClassSelector& race_and_class_selector,
    GameStateMonitor& game_state_monitor)
    : Button(button_area, viewport, renderer),
      socket_manager(socket_manager),
      character_name_input(character_name_input),
      race_and_class_selector(race_and_class_selector),
      game_state_monitor(game_state_monitor) {}

void RequestCharacterCreationButton::on_click() {
    ResourceManager::get_instance().get_sound_fx(3).play();
    socket_manager.send(EventFactory::create_event(
        character_name_input.get_text(),
        race_and_class_selector.get_selected_class(),
        race_and_class_selector.get_selected_race()));
    game_state_monitor.set_game_state(WAITING_FOR_INITIALIZATION);
}