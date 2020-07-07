#include <iostream>
#include "cast_button.h"
#include "../../engine/sound_system.h"

CastButton::CastButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, bool& attempting_cast)
    : Button(button_area, viewport, renderer),
      attempting_cast(attempting_cast) {}

void CastButton::on_click() {
    std::cout << "Cast button clicked" << std::endl;
    SoundSystem::get_instance().play_ui_sfx(3);
    attempting_cast = true;
}