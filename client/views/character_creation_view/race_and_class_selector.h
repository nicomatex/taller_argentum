#ifndef __RACE_AND_CLASS_SELECTOR_H
#define __RACE_AND_CLASS_SELECTOR_H
#include "option_button.h"
#include "../responsive_scaler.h"

class RaceAndClassSelector{
    character_option_t selected_race;
    character_option_t selected_class;
    OptionButton human_button;
    OptionButton elf_button;
    OptionButton dwarf_button;
    OptionButton gnome_button;
    OptionButton mage_button;
    OptionButton priest_button;
    OptionButton paladin_button;
    OptionButton warrior_button;

    public:
    RaceAndClassSelector(ResponsiveScaler &scaler, SDL_Renderer* renderer);
    ~RaceAndClassSelector();

    void handle_event(SDL_Event &e);
    character_option_t get_selected_race();
    character_option_t get_selected_class();
    
};

#endif