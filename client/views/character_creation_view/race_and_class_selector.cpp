#include "race_and_class_selector.h"

#include "../../client_config.h"

RaceAndClassSelector::RaceAndClassSelector(ResponsiveScaler& scaler,
                                           SDL_Renderer* renderer)
    : selected_class(WARRIOR),
      selected_race(HUMAN),
      human_button(scaler.scale(HUMAN_BUTTON_AREA),
                   scaler.scale(CHAR_CREATION_VIEWPORT), renderer, HUMAN,
                   selected_race),
      elf_button(scaler.scale(ELF_BUTTON_AREA),
                 scaler.scale(CHAR_CREATION_VIEWPORT), renderer, ELF,
                 selected_race),
      dwarf_button(scaler.scale(DWARF_BUTTON_AREA),
                   scaler.scale(CHAR_CREATION_VIEWPORT), renderer, DWARF,
                   selected_race),
      gnome_button(scaler.scale(GNOME_BUTTON_AREA),
                   scaler.scale(CHAR_CREATION_VIEWPORT), renderer, GNOME,
                   selected_race),
      mage_button(scaler.scale(MAGE_BUTTON_AREA),
                  scaler.scale(CHAR_CREATION_VIEWPORT), renderer, MAGE,
                  selected_class),
      priest_button(scaler.scale(PRIEST_BUTTON_AREA),
                    scaler.scale(CHAR_CREATION_VIEWPORT), renderer, PRIEST,
                    selected_class),
      paladin_button(scaler.scale(PALADIN_BUTTON_AREA),
                     scaler.scale(CHAR_CREATION_VIEWPORT), renderer, PALADIN,
                     selected_class),
      warrior_button(scaler.scale(WARRIOR_BUTTON_AREA),
                     scaler.scale(CHAR_CREATION_VIEWPORT), renderer, WARRIOR,
                     selected_class) {}

RaceAndClassSelector::~RaceAndClassSelector() {}

void RaceAndClassSelector::handle_event(SDL_Event& e) {
    human_button.handle_event(e);
    elf_button.handle_event(e);
    dwarf_button.handle_event(e);
    gnome_button.handle_event(e);
    mage_button.handle_event(e);
    priest_button.handle_event(e);
    paladin_button.handle_event(e);
    warrior_button.handle_event(e);
}

character_option_t RaceAndClassSelector::get_selected_class(){
    return selected_class;
}

character_option_t RaceAndClassSelector::get_selected_race(){
    return selected_race;
}