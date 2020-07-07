#ifndef __LOGIN_BUTTON_H
#define __LOGIN_BUTTON_H
#include "../../../include/network/socket_manager.h"
#include "../../engine/UI/button.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"

/**
 * @brief Boton para iniciar sesion.
 * 
 */
class LoginButton : public Button {
    GameStateMonitor& game_state_monitor;
    SocketManager& socket_manager;
    TextInput& character_name_input;

   public:
    /**
     * @brief Crea un objeto Login Button
     * 
     * @param button_area Area del boton
     * @param viewport Viewport donde esta el boton.
     * @param renderer Renderer con el que se va a mostrar el boton.
     * @param game_state_monitor Monitor de estado de juego.
     * @param socket_manager Socket manager del juego.
     * @param character_name_input Input del nobmre de personaje.
     */
    LoginButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
                GameStateMonitor& game_state_monitor,
                SocketManager& socket_manager,
                TextInput& character_name_input);
    
    /**
     * @brief Envia el evento de inicio de sesion.
     * 
     */
    void on_click() override;
};

#endif