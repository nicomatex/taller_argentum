#include "inventory.h"

#include "../../client_config.h"
#include "../../network/event_factory.h"

Inventory::Inventory(SDL_Rect inventory_area, SDL_Rect viewport, int rows,
                     int cols, TTF_Font* numbers_font, SDL_Renderer* renderer,
                     SocketManager& socket_manager)
    : last_clicked_slot(0),
      renderer(renderer),
      inventory_icons(inventory_area, renderer, rows, cols, 1),
      item_qty_grid(inventory_area, rows, cols, numbers_font, renderer),
      item_button_grid(inventory_area, viewport, renderer, rows, cols,
                       last_clicked_slot, socket_manager,
                       EventFactory::inventory_event,
                       EventFactory::drop_item_event) {}

Inventory::~Inventory() {}

void Inventory::_render_slot_outline() {
    SDL_Rect rect_area = inventory_icons.get_icon_area(last_clicked_slot);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&rect_area);
}

void Inventory::render() {
    inventory_icons.render();
    item_qty_grid.render();
    _render_slot_outline();
}

void Inventory::set_item(int slot, SDLTexture* icon, int quantity) {
    inventory_icons.set_icon(slot, icon);
    item_qty_grid.set_quantity(slot, quantity);
}

void Inventory::handle_event(SDL_Event& e) { item_button_grid.handle_event(e); }

int Inventory::get_last_clicked_slot() { return last_clicked_slot; }