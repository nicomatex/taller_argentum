#ifndef __GO_BACK_BUTTON_H
#define __GO_BACK_BUTTON_H
#include "../../engine/UI/button.h"
#include "../../game_state_monitor.h"

/**
 * @brief Boton de "volver" de la pantalla de 
 * creacion de personajes.
 * 
 */
class GoBackButton : public Button{
    private:
        GameStateMonitor& game_state_monitor;
        
    public:
        /**
         * @brief Constructor del boton de "volver".
         * 
         * @param button_area Area donde se va a renderizar el boton.
         * @param viewport Viewport en el cual esta el boton.
         * @param renderer Renderer con el cual se va a renderizar el boton.
         * @param game_state_monitor Monitor de estado del juego.
         */
        GoBackButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
                GameStateMonitor& game_state_monitor);
        
        void on_click() override;
};

#endif