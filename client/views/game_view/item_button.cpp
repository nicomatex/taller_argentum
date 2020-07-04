#include "item_button.h"

#include <iostream>
#include "../../engine/resource_manager.h"
#include "../../network/event_factory.h"

ItemButton::ItemButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, SlotId slot_number,
                       SocketManager& socket_manager)
    : Button(button_area, viewport, renderer),
      slot_number(slot_number),
      socket_manager(socket_manager) {}

void ItemButton::on_click() {
    if (!double_click_timer.is_started()) {
        double_click_timer.start();
        return;
    }
    if (double_click_timer.get_ticks() <= 500) {
        socket_manager.send(EventFactory::inventory_event(slot_number));
		ResourceManager::get_instance().get_sound_fx(3).play();
		double_click_timer.stop();
    }else{
		double_click_timer.start();
	}
	
}
