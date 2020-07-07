#include "item_button.h"

#include <iostream>

#include "../../engine/sound_system.h"
#include "../../network/event_factory.h"

ItemButton::ItemButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, SlotId slot_number,
                       int& last_clicked_slot, SocketManager& socket_manager)
    : Button(button_area, viewport, renderer),
      slot_number(slot_number),
      last_clicked_slot(last_clicked_slot),
      socket_manager(socket_manager) {}

void ItemButton::on_click() {
    last_clicked_slot = slot_number;
    if (!double_click_timer.is_started()) {
        double_click_timer.start();
        return;
    }
    if (double_click_timer.get_ticks() <= 500) {
        socket_manager.send(EventFactory::inventory_event(slot_number));
        SoundSystem::get_instance().play_ui_sfx(3);

        double_click_timer.stop();
    } else {
        double_click_timer.start();
    }
}

void ItemButton::on_right_click() {
    std::cout << "Sending drop event on slot " << slot_number << std::endl;
    socket_manager.send(EventFactory::drop_item_event(slot_number));
}