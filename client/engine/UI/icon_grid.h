#ifndef __ICON_GRID_H
#define __ICON_GRID_H

#include "SDL2/SDL.h"
#include "../SDL/sdl_texture.h"
#include <vector>

class IconGrid{
    private:
        SDL_Rect render_area;
        SDL_Renderer* renderer;
        int icon_width;
        int icon_height;
        int cols;
        int rows;
        std::vector<SDLTexture*> icons;

    public:
        IconGrid(SDL_Rect render_area,SDL_Renderer* renderer,int rows,int cols);
        ~IconGrid();
        
        /* Inserta un icono en la posicion indicada. Las posiciones
        se numeran de izquierda a derecha y de arriba hacia abajo 
        (es decir, el icono de arriba a la izquierda es la posicion 0
        y el icono de abajo a la derecha es la posicion rows * cols - 1
        Para quitar un icono, se debe pasar un NULL para la posicion.*/
        void set_icon(int position, SDLTexture* icon);
        void render();
};

#endif