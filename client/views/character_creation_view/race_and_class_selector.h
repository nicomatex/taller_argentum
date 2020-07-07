#ifndef __RACE_AND_CLASS_SELECTOR_H
#define __RACE_AND_CLASS_SELECTOR_H

#include "../../../include/types.h"
#include "../responsive_scaler.h"
#include "option_button.h"

/**
 * @brief Wrapper del conjunto de botones de seleccion
 * de raza y clase.
 * 
 */
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
    /**
     * @brief Selector de Raza y Clase. Encapsula todos los botones.
     * 
     * @param scaler Escalador para responsiveness.
     * @param renderer Renderer con el cual se va a renderizar el selector.
     */
    RaceAndClassSelector(ResponsiveScaler &scaler, SDL_Renderer *renderer);
    ~RaceAndClassSelector();

    void handle_event(SDL_Event &e);

    /**
     * @brief Devuelve la raza seleccionada.
     * 
     * @return race_type_t 
     */
    race_type_t get_selected_race();

    /**
     * @brief Devuelve la clase seleccionada.
     * 
     * @return class_type_t 
     */
    class_type_t get_selected_class();
};

#endif