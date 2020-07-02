#include "request_char_creation_button.h"
#include "../../engine/resource_manager.h"

RequestCharacterCreationButton::RequestCharacterCreationButton(
    SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
    SocketManager& socket_manager)
    : Button(button_area, viewport, renderer), socket_manager(socket_manager) {}

void RequestCharacterCreationButton::on_click() {
    ResourceManager::get_instance().get_sound_fx(3).play();
    // TODO
}