#include "in_game_bar.h"

#include "resource_manager.h"

InGameBar::InGameBar(visual_info_t visual_info)
    : RenderizableObject(visual_info),
      fill_proportion(1),
      bar_texture(
          ResourceManager::get_instance().get_texture("interface", 24)) {}

void InGameBar::set_fill_proportion(float fill_proportion) {
    this->fill_proportion = fill_proportion;
}

void InGameBar::render(SDL_Rect dest) {
    dest.w *= fill_proportion;
    uint8_t red = (uint8_t)(-255 * fill_proportion + 255);
    uint8_t green = (uint8_t)(255 * fill_proportion);
    uint32_t blue = 0;
    bar_texture.set_color_mod(red, green, blue);
    bar_texture.render(dest);
    bar_texture.reset_color_mod();
}