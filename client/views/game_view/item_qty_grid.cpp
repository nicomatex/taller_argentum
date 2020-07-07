#include "item_qty_grid.h"

#include "../../client_config.h"
#include "../../engine/resource_manager.h"

ItemQtyGrid::ItemQtyGrid(SDL_Rect inventory_area, int rows, int cols,
                         TTF_Font* numbers_font, SDL_Renderer* renderer)
    : number_grid(inventory_area, renderer, rows, cols, 0.4, true) {
    for (int i = 0; i < rows * cols; i++) {
        quantities.push_back(
            SDLText("0", numbers_font, INVENTORY_QTIES_COLOR, renderer));
    }
}

ItemQtyGrid::~ItemQtyGrid() {}

void ItemQtyGrid::set_quantity(int slot, int quantity) {
    if (quantity == 0) {
        number_grid.set_icon(slot, NULL);
        return;
    }
    quantities[slot].update_text(std::to_string(quantity));
    number_grid.set_icon(slot, &(quantities[slot]));
}

void ItemQtyGrid::render() { number_grid.render(); }