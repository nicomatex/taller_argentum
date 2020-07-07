#ifndef __ITEM_QTY_GRID_H
#define __ITEM_QTY_GRID_H
#include <vector>

#include "../../engine/SDL/sdl_text.h"
#include "../../engine/UI/icon_grid.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

/**
 * @brief Utilizada para renderizar las cantidades de los items en el
 * inventario.
 *
 */
class ItemQtyGrid {
   private:
    IconGrid number_grid;
    std::vector<SDLText> quantities;

   public:
    /**
     * @brief Crea un objeto Item Qty Grid
     *
     * @param inventory_area Area del inventario.
     * @param rows Filas del inventario.
     * @param cols Columnas del inventario.
     * @param numbers_font Fuente a usar para los numeros.
     * @param renderer Renderer a utilizar para las cantidades.
     */
    ItemQtyGrid(SDL_Rect inventory_area, int rows, int cols,
                TTF_Font* numbers_font, SDL_Renderer* renderer);
    ~ItemQtyGrid();

    /* Setea la cantidad a mostrar en un determinado slot. Si la cantidad
    es 0, el numero no se renderiza. */

    /**
     * @brief Setea la cantidad de un item que hay en un slot
     *
     * @details Si se pasa quantity 0, el numero no se renderiza.
     *
     * @param slot
     * @param quantity
     */
    void set_quantity(int slot, int quantity);

    /**
     * @brief Renderiza las cantidades de los objetos.
     *
     */
    void render();
};

#endif