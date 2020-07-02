#include "option_button.h"

#include <iostream>

#include "../../engine/resource_manager.h"

OptionButton::OptionButton(SDL_Rect button_area, SDL_Rect viewport,
                           SDL_Renderer* renderer,
                           character_option_t this_button_option,
                           character_option_t& selected_option)
    : Button(button_area, viewport, renderer),
      this_button_option(this_button_option),
      selected_option(selected_option) {}

OptionButton::~OptionButton() {}

void OptionButton::on_click() {
    selected_option = this_button_option;
    ResourceManager::get_instance().get_sound_fx(3).play();
}