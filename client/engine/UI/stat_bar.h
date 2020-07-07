#ifndef __STAT_BAR_H
#define __STAT_BAR_H

#include "../SDL/sdl_text.h"
#include "SDL2/SDL.h"

/**
 * @brief Barra de stat, usado en HP, MP y Experiencia.
 * 
 */
class StatBar {
   private:
    SDL_Renderer* renderer;
    SDL_Rect render_area;
    SDL_Color bar_color;
    SDLText render_text;
    unsigned int max_value;
    unsigned int current_value;

    void _render_bar();
    void _render_text();

   public:
   /**
    * @brief Crea un objeto StatBar
    * 
    * @param render_area Area donde se va a renderizar la statbar en pantalla.
    * @param font Fuente tipografica para los numeros.
    * @param renderer Renderer con el cual se va a renderizar la statbar.
    * @param max_value Maximo valor que puede tomar el stat representado.
    * @param bar_color Color de la barra.
    * @param text_color Color de los numeros.
    */
    StatBar(SDL_Rect render_area, TTF_Font* font, SDL_Renderer* renderer,
            unsigned int max_value, SDL_Color bar_color, SDL_Color text_color);
    ~StatBar();

    /**
     * @brief Setea el valor actual del stat.
     * 
     * @details Si es mayor al valor maximo, se trunca al valor maximo.
     * 
     * @param new_current_value Nuevo valor actual.
     */
    void set_current_value(unsigned int new_current_value);

    /**
     * @brief Setea el nuevo valor maximo del stat.
     * 
     * @param new_max_value Nuevo valor maximo.
     */
    void set_max_value(unsigned int new_max_value);

    /**
     * @brief Renderiza la statbar.
     * 
     */
    void render();
};

#endif