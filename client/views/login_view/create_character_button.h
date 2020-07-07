#ifndef __CREATE_CHARACTER_BUTTON
#define __CREATE_CHARACTER_BUTTON
#include "../../engine/UI/button.h"
#include "../../game_state_monitor.h"

/**
 * @brief Boton para cambiar a la vista de creacion de personaje.
 *
 */
class CreateCharacterButton : public Button {
   private:
    GameStateMonitor& game_state_monitor;

   public:
    /**
     * @brief Crea un CreateCharacterButton
     *
     * @param button_area Area del boton.
     * @param viewport Viewport donde esta el boton.
     * @param renderer Renderer donde esta el boton.
     * @param game_state_monitor Monitor de estado del juego.
     */
    CreateCharacterButton(SDL_Rect button_area, SDL_Rect viewport,
                          SDL_Renderer* renderer,
                          GameStateMonitor& game_state_monitor);

    /**
     * @brief Cambia la vista a creacion de personaje.
     *
     */
    void on_click() override;
};

#endif