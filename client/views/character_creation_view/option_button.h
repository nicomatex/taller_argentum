#ifndef __OPTION_BUTTON_H
#define __OPTION_BUTTON_H

#include "../../engine/UI/button.h"
#include "../../engine/resource_manager.h"

template <typename T>
class OptionButton : public Button {
   private:
    T& selected_option;
    T this_button_option;

   public:
    OptionButton(SDL_Rect button_area, SDL_Rect viewport,
                 SDL_Renderer* renderer, T this_button_option,
                 T& selected_option)
        : Button(button_area, viewport, renderer),
          this_button_option(this_button_option),
          selected_option(selected_option) {}

    void on_click() override {
        selected_option = this_button_option;
        ResourceManager::get_instance().get_sound_fx(3).play();
    }
};

#endif