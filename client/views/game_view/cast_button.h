#ifndef __CAST_BUTTON_H
#define __CAST_BUTTON_H

#include "../../engine/UI/button.h"

/**
 * @brief Boton de "Lanzar" en el juego.
 * 
 */
class CastButton : public Button {
   private:
    bool& attempting_cast;

   public: 
    /**
     * @brief Crea un objeto Cast Button
     * 
     * @param attemtping_cast Booleano que el boton modifica al clickear el boton 
     * de cast. Indica intenciones de castear un hechizo.
     */
    CastButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
               bool& attemtping_cast);

    void on_click() override;
};

#endif