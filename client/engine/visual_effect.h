#ifndef __VISUAL_EFFECT_H
#define __VISUAL_EFFECT_H
#include "renderizable_object.h"

/**
 * @brief Clase para mostrar efectos visuales en posiciones dinamicas.
 * 
 */
class VisualEffect: public RenderizableObject{
    private:
        SDLSprite sprite;

    public:
        VisualEffect(SDLSprite &sprite, visual_info_t visual_info);

        /**
         * @brief Renderiza el efecto en pantalla.
         * 
         * @param dest Rectangulo de la pantalla donde se va a renderizar.
         */
        void render(SDL_Rect dest) override;
};


#endif