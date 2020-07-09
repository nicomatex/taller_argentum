#ifndef __OPTION_BUTTON_H
#define __OPTION_BUTTON_H

#include "../../engine/UI/button.h"
#include "../../engine/sound_system.h"

/**
 * @brief Boton de seleccion de opcion.
 *
 * @tparam T Clase de la opcion. Se utiliza alternativamente RAZA o CLASE.
 */
template <typename T>
class OptionButton : public Button {
   private:
    T this_button_option;
    T& selected_option;

   public:
    /**
     * @brief Boton perteneciente a opciones multiples.
     *
     * @param button_area Area donde se va a renderizar el boton
     * @param viewport Viewport donde esta el boton
     * @param renderer Renderer con el que se va a renderizar el boton.
     * @param this_button_option Opcion que representa esta instancia del boton.
     * @param selected_option Referencia al parametro que se debe modificar al
     * clickear el boton.
     */
    OptionButton(SDL_Rect button_area, SDL_Rect viewport,
                 SDL_Renderer* renderer, T this_button_option,
                 T& selected_option)
        : Button(button_area, viewport, renderer),
          this_button_option(this_button_option),
          selected_option(selected_option) {}

    /**
     * @brief Setea la seleccion a la opcion representada por este boton.
     *
     */
    void on_click() override {
        selected_option = this_button_option;
        SoundSystem::get_instance().play_ui_sfx(3);
    }
};

#endif