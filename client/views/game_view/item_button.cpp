#include "item_button.h"
#include "../../network/event_factory.h"
#include <iostream>

ItemButton::ItemButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, SlotId slot_number,
                       SocketManager& socket_manager)
    : Button(button_area, viewport, renderer),
      slot_number(slot_number),
      socket_manager(socket_manager) {}

void ItemButton::on_click() {
    std::cerr << "Boton numero " << slot_number << " clickeado" << std::endl;
    socket_manager.send(EventFactory::inventory_event(slot_number));
}
