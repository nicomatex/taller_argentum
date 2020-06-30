#ifndef __RESPONSIVE_SCALER_H
#define __RESPONSIVE_SCALER_H
#include "SDL2/SDL.h"
#include "../engine/SDL/sdl_window.h"

class ResponsiveScaler {
   private:
    SDLWindow &window;
    float scale_factor_w;
    float scale_factor_h;

   public:
    ResponsiveScaler(SDLWindow &window, int prototype_width,
                     int prototype_height);
    ~ResponsiveScaler();

    /* Devuelve un SDL_Rect escalado segun los factores de la ventana.*/
    SDL_Rect scale(SDL_Rect unscaled_rect);

    /* Devuelve un valor escalado segun el factor de escalado de ancho. */
    int simple_scale(int dimension);
};

#endif