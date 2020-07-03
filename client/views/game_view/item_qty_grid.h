#ifndef __ITEM_QTY_GRID_H
#define __ITEM_QTY_GRID_H
#include "../../engine/UI/icon_grid.h"
#include "../../engine/SDL/sdl_text.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>

class ItemQtyGrid {
   private:
    IconGrid number_grid;
    std::vector<SDLText> quantities;

   public:
    ItemQtyGrid(SDL_Rect inventory_area, int rows, int cols,
              TTF_Font* numbers_font, SDL_Renderer* renderer);
    ~ItemQtyGrid();

    /* Setea la cantidad a mostrar en un determinado slot. Si la cantidad
    es 0, el numero no se renderiza. */
    void set_quantity(int slot,int quantity);

    void render();
};

#endif