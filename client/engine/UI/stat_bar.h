#ifndef __STAT_BAR_H
#define __STAT_BAR_H

#include "../SDL/sdl_text.h"
#include "SDL2/SDL.h"

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
    StatBar(SDL_Rect render_area, TTF_Font* font, SDL_Renderer* renderer,
            unsigned int max_value, SDL_Color bar_color, SDL_Color text_color);
    ~StatBar();

    /* Setea el valor actual del stat que se representa en la barra.
    Si es mayor al valor maximo, se trunca al valor maximo.
    void set_current_value(unsigned int new_current_value);*/
    void set_current_value(unsigned int new_current_value);
    /* Setea el valor maximo del stat que se representa en la barra. Debe ser
    un entero positivo.*/
    void set_max_value(unsigned int new_max_value);
    void render();
};

#endif