#ifndef __RESPONSIVE_SCALER_H
#define __RESPONSIVE_SCALER_H
#include "../engine/SDL/sdl_window.h"
#include "SDL2/SDL.h"

/**
 * @brief Escalador para hacer las areas responsive.
 *
 */
class ResponsiveScaler {
   private:
    SDLWindow &window;
    float scale_factor_w;
    float scale_factor_h;

   public:
    /**
     * @brief Crea un objeto Responsive Scaler
     *
     * @param window Ventana para la cual se desean generar las areas
     * responsive.
     * @param prototype_width Ancho "prototipo", en base al cual se escalara
     * todo.
     * @param prototype_height Alto "prototipo", en base al cual se escalara
     * todo.
     */
    ResponsiveScaler(SDLWindow &window, int prototype_width,
                     int prototype_height);
    ~ResponsiveScaler();

    /**
     * @brief Devuelve un SDL_Rect escalado segun los factores de la ventana.
     * 
     * @param unscaled_rect Rectangulo sin escalar o prototipo.
     * @return SDL_Rect 
     */
    SDL_Rect scale(SDL_Rect unscaled_rect);

    /**
     * @brief Escala simple, segun el factor de escalado en anchura.
     * 
     * @param dimension Dimension sin escalar o prototipo.
     * @return int 
     */
    int tile_scale(int dimension);

};

#endif