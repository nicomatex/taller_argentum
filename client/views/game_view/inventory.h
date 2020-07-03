#ifndef __INVENTORY_H
#define __INVENTORY_H
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/UI/icon_grid.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "item_button_grid.h"
#include "item_qty_grid.h"

class Inventory {
   private:
    IconGrid inventory_icons;
    SDL_Rect inventory_area;
    ItemQtyGrid item_qty_grid;
    ItemButtonGrid item_button_grid;

   public:
    Inventory(SDL_Rect inventory_area, SDL_Rect viewport, int rows, int cols,
              TTF_Font* numbers_font, SDL_Renderer* renderer,
              SocketManager& socket_manager);
    ~Inventory();

    void render();
    void set_item(int slot, SDLTexture* icon, int quantity);
    void handle_event(SDL_Event& e);
};

#endif