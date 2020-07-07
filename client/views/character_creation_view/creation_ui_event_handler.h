#ifndef __CREATION_UI_EVENT_HANDLER
#define __CREATION_UI_EVENT_HANDLER

#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "go_back_button.h"
#include "race_and_class_selector.h"
#include "request_char_creation_button.h"

/**
 * @brief Handler de eventos de usuario de la pantalla de
 * creacion de personajes.
 * 
 */
class CreationUiEventHandler {
    TextInput& character_name_input;
    GameStateMonitor& game_state_monitor;
    RaceAndClassSelector& race_and_class_selector;
    GoBackButton& go_back_button;
    RequestCharacterCreationButton& req_char_creation_button;

   public:
    /**
     * @brief Handler de eventos de la interfaz de usuario de la vista de juego.
     *
     * @param character_name_input TextInput del nombre de jugador.
     * @param race_and_class_selector Selector de raza y clase.
     * @param go_back_button Boton de volver.
     * @param req_char_creation_button Boton de "crear personaje".
     * @param game_state_monitor Monitor de estado del juego.
     */
    CreationUiEventHandler(
        TextInput& character_name_input,
        RaceAndClassSelector& race_and_class_selector,
        GoBackButton& go_back_button,
        RequestCharacterCreationButton& req_char_creation_button,
        GameStateMonitor& game_state_monitor);
    ~CreationUiEventHandler();

    void handle();
};

#endif