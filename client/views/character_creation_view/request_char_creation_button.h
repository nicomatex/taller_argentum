#ifndef __CHAR_CREATION_BUTTON_H
#define __CHAR_CREATION_BUTTON_H

#include "../../../include/network/socket_manager.h"
#include "../../engine/UI/button.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "race_and_class_selector.h"

/**
 * @brief Boton de "Crear Personaje" en la vista
 * de creacion de personaje.
 * 
 */
class RequestCharacterCreationButton : public Button {
   private:
    SocketManager& socket_manager;
    TextInput& character_name_input;
    RaceAndClassSelector& race_and_class_selector;
    GameStateMonitor& game_state_monitor;

   public:
    /**
     * @brief Boton de "Crear Personaje."
     *
     * @param button_area Area donde se va a renderizar el boton.
     * @param viewport Viewport donde esta el boton.
     * @param renderer Renderer con el que se va a renderizar el boton.
     * @param socket_manager Socket manager del juego.
     * @param character_name_input Input de nombre de personaje
     * @param race_and_class_selector Selector de raza y clase
     * @param game_state_monitor Monitor de estado del juego
     */
    RequestCharacterCreationButton(
        SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
        SocketManager& socket_manager, TextInput& character_name_input,
        RaceAndClassSelector& race_and_class_selector,
        GameStateMonitor& game_state_monitor);

    /**
     * @brief Envia el evento de creacion de personaje al servidor, con los
     * parametros seleccionados en la interfaz (nombre, raza y clase).
     *
     */
    void on_click() override;
};

#endif