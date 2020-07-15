#include "equipment.h"

#include "../../client_config.h"
#include "../../network/event_factory.h"

Equipment::Equipment(SDL_Rect equipment_area, SDL_Rect viewport,
                     SDL_Renderer* renderer, SocketManager& socket_manager)
    : last_clicked_slot(0),
      equipment_icons(equipment_area, renderer, EQUIPMENT_ROWS, EQUIPMENT_COLS,
                      1),
      item_button_grid(equipment_area, viewport, renderer, EQUIPMENT_ROWS,
                       EQUIPMENT_COLS, last_clicked_slot, socket_manager,
                       EventFactory::unequip_event, nullptr) {}
Equipment::~Equipment() {}

void Equipment::render() { equipment_icons.render(); }

void Equipment::set_item(int slot, SDLTexture* icon) {
    equipment_icons.set_icon(slot, icon);
}

void Equipment::handle_event(SDL_Event& e) { item_button_grid.handle_event(e); }

int Equipment::get_last_clicked_slot() { return last_clicked_slot; }
