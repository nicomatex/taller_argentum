#ifndef __LOGIN_VIEW_H
#define __LOGIN_VIEW_H
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/text_input.h"
#include "../../game_state_monitor.h"
#include "../responsive_scaler.h"
#include "../../../include/network/socket_manager.h"
#include "login_button.h"
#include "create_character_button.h"
#include "login_view_ui_handler.h"

/**
 * @brief Vista de inicio de sesion.
 * 
 */
class LoginView {
   private:
    SDLWindow &window;
    ResponsiveScaler &scaler;
    SDLTexture &background;
    GameStateMonitor &game_state_monitor;
    TextInput character_name_input;
    LoginButton login_button;
    CreateCharacterButton create_character_button;
    LoginUiEventHandler ui_event_handler;

    void render_login_alert();
    
   public:
    /**
     * @brief Crea un objeto Login View
     * 
     * @param window Ventana dodne se va a mostrar la vista.
     * @param scaler Escalador para responsiveness.
     * @param game_state_monitor Monitor de estado de juego.
     * @param socket_manager Socket Manager del juego.
     */
    LoginView(SDLWindow &window, ResponsiveScaler &scaler,
              GameStateMonitor &game_state_monitor,
              SocketManager &socket_manager);
    ~LoginView();

    /**
     * @brief Inicia la vista.
     * 
     */
    void run(int fps);
};

#endif