#ifndef __RACE_BUTTON_H
#define __RACE_BUTTON_H
#include "../../engine/UI/button.h"

typedef enum {
    HUMAN,
    ELF,
    DWARF,
    GNOME,
    MAGE,
    PRIEST,
    PALADIN,
    WARRIOR
} character_option_t;

class OptionButton : public Button {
   private:
    character_option_t& selected_option;
    character_option_t this_button_option;

   public:
    OptionButton(SDL_Rect button_area, SDL_Rect viewport,
                 SDL_Renderer* renderer, character_option_t this_button_option,
                 character_option_t& selected_option);
    ~OptionButton();

    void on_click() override;
};

#endif