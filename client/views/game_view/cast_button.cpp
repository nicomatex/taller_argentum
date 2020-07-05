#include "cast_button.h"

#include <iostream>

#include "../../engine/resource_manager.h"
CastButton::CastButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, bool& attempting_cast)
    : Button(button_area, viewport, renderer),
      attempting_cast(attempting_cast) {}

void CastButton::on_click() {
    std::cout << "Cast button clicked" << std::endl;
    ResourceManager::get_instance().get_sound_fx(3).play();
    attempting_cast = true;
}