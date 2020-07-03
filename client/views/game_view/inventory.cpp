#include "inventory.h"

#include "../../client_config.h"

Inventory::Inventory(SDL_Rect inventory_area, SDL_Rect viewport, int rows,
                     int cols, TTF_Font* numbers_font, SDL_Renderer* renderer,
                     SocketManager& socket_manager)
    : inventory_icons(inventory_area, renderer, rows, cols, 1),
      item_qty_grid(inventory_area, rows, cols, numbers_font, renderer),
      item_button_grid(inventory_area, viewport, renderer, rows, cols,
                       socket_manager) {}

Inventory::~Inventory() {}

void Inventory::render() {
    inventory_icons.render();
    item_qty_grid.render();
}

void Inventory::set_item(int slot, SDLTexture* icon, int quantity) {
    inventory_icons.set_icon(slot, icon);
    item_qty_grid.set_quantity(slot, quantity);
}

void Inventory::handle_event(SDL_Event& e) { item_button_grid.handle_event(e); }