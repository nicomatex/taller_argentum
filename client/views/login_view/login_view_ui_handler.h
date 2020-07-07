#ifndef __LOGIN_UI_EVENT_HANDLER
#define __LOGIN_UI_EVENT_HANDLER

#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "create_character_button.h"
#include "login_button.h"

/**
 * @brief Handler de eventos del usuario de la vista
 * de inicio de sesion.
 * 
 */
class LoginUiEventHandler {
   private:
    TextInput& character_name_input;
    GameStateMonitor& game_state_monitor;
    LoginButton& login_button;
    CreateCharacterButton& create_character_button;

   public:
    /**
     * @brief Crea un objeto Login Ui Event Handler
     *
     * @param character_name_input Input de nombre de personaje.
     * @param login_button Boton  de "Conectar"
     * @param create_character_button Boton para ir a la vista de crear
     * personaje.
     * @param game_state_monitor Monitor de estado de juego.
     */
    LoginUiEventHandler(TextInput& character_name_input,
                        LoginButton& login_button,
                        CreateCharacterButton& create_character_button,
                        GameStateMonitor& game_state_monitor);
    ~LoginUiEventHandler();
    void handle();
};

#endif