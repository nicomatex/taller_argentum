#ifndef __ITEM_BUTTON_GRID_H
#define __ITEM_BUTTON_GRID_H

#include <vector>

#include "SDL2/SDL.h"
#include "item_button.h"

class ItemButtonGrid {
   private:
    std::vector<ItemButton> buttons;
    int last_clicked_slot;

   public:
    ItemButtonGrid(SDL_Rect inventory_area, SDL_Rect viewport,
                   SDL_Renderer* renderer, int rows, int cols,
                   SocketManager& socket_manager);
    ~ItemButtonGrid();

    void handle_event(SDL_Event& e);

    int get_last_clicked_slot();
};

#endif