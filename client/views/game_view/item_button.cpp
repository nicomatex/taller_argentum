#include "item_button.h"

#include <iostream>

#include "../../client_config.h"
#include "../../engine/sound_system.h"

ItemButton::ItemButton(SDL_Rect button_area, SDL_Rect viewport,
                       SDL_Renderer* renderer, SlotId slot_number,
                       int& last_clicked_slot, SocketManager& socket_manager,
                       Event (*left_click_event)(SlotId),
                       Event (*right_click_event)(SlotId))
    : Button(button_area, viewport, renderer),
      slot_number(slot_number),
      last_clicked_slot(last_clicked_slot),
      socket_manager(socket_manager),
      left_click_event(left_click_event),
      right_click_event(right_click_event) {}

void ItemButton::on_click() {
    if (!left_click_event)
        return;
    last_clicked_slot = slot_number;
    if (!double_click_timer.is_started()) {
        double_click_timer.start();
        return;
    }
    if (double_click_timer.get_ticks() <= DOUBLE_CLICK_DELAY) {
        socket_manager.send(left_click_event(slot_number));
        SoundSystem::get_instance().play_ui_sfx(3);

        double_click_timer.stop();
    } else {
        double_click_timer.start();
    }
}

void ItemButton::on_right_click() {
    if (!right_click_event)
        return;
    socket_manager.send(right_click_event(slot_number));
}