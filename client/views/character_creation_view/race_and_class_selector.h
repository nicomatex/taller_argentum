#ifndef __RACE_AND_CLASS_SELECTOR_H
#define __RACE_AND_CLASS_SELECTOR_H

#include "../../../include/types.h"
#include "../responsive_scaler.h"
#include "option_button.h"

class RaceAndClassSelector {
    race_type_t selected_race;
    class_type_t selected_class;
    OptionButton<race_type_t> human_button;
    OptionButton<race_type_t> elf_button;
    OptionButton<race_type_t> dwarf_button;
    OptionButton<race_type_t> gnome_button;
    OptionButton<class_type_t> mage_button;
    OptionButton<class_type_t> priest_button;
    OptionButton<class_type_t> paladin_button;
    OptionButton<class_type_t> warrior_button;

   public:
    RaceAndClassSelector(ResponsiveScaler &scaler, SDL_Renderer *renderer);
    ~RaceAndClassSelector();

    void handle_event(SDL_Event &e);
    race_type_t get_selected_race();
    class_type_t get_selected_class();
};

#endif