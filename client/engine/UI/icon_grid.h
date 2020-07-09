#ifndef __ICON_GRID_H
#define __ICON_GRID_H

#include <vector>

#include "../SDL/sdl_texture.h"
#include "SDL2/SDL.h"

/**
 * @brief Cuadricula de iconos
 * 
 */
class IconGrid {
   private:
    SDL_Rect render_area;
    SDL_Renderer* renderer;
    int icon_width;
    int icon_height;
    int rows;
    int cols;
    float size_proportion;
    bool original_proportions;

    /* Indica que proporcion del cuadrito correspondiente ocupa el icono. Va de
     * 0 a 1.*/

    std::vector<SDLTexture*> icons;

   public:
    /**
     * @brief Crea un objeto Icon Grid
     *
     * @param render_area Area donde se va a renderizar el icongrid.
     * @param renderer Renderer con el cual se va a renderizar.
     * @param rows Cantidad de filas de la grilla.
     * @param cols Cantidad de columnas de la grilla.
     * @param size_proportion Proporcion de tamanio de cada cuadro que ocuparan
     * los iconos. Debe ir entre 0 y 1.
     * @param original_proportions indica si se debe resizear los iconos para
     * que matcheen el tamanio de cada cuadradito, o si se debe conservar las
     * proporciones de la textura original.
     */
    IconGrid(SDL_Rect render_area, SDL_Renderer* renderer, int rows, int cols,
             float size_proportion, bool original_proportions = false);
    ~IconGrid();

    /* Inserta un icono en la posicion indicada. */

    /**
     * @brief Setea el icono en una posicion dada.
     *
     * @details Las posiciones
     * se numeran de izquierda a derecha y de arriba hacia abajo
     * (es decir, el icono de arriba a la izquierda es la posicion 0
     * y el icono de abajo a la derecha es la posicion rows * cols - 1
     * Para quitar un icono, se debe pasar un NULL para la posicion.
     *
     * @param position
     * @param icon
     */
    void set_icon(int position, SDLTexture* icon);

    /**
     * @brief Renderiza el icongrid.
     *
     */
    void render();
};

#endif