#include "item_button_grid.h"

ItemButtonGrid::ItemButtonGrid(SDL_Rect inventory_area, SDL_Rect viewport,
                               SDL_Renderer* renderer, int rows, int cols,
                               SocketManager& socket_manager,
                               Event (*left_click_event)(SlotId),
                               Event (*right_click_event)(SlotId))
    : last_clicked_slot(0) {
    int button_width = inventory_area.w / cols;
    int button_height = inventory_area.h / rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int vector_position = j + i * cols;
            SDL_Rect button_area = {inventory_area.x + j * button_width,
                                    inventory_area.y + i * button_height,
                                    button_width, button_height};
            buttons.push_back(ItemButton(button_area, viewport, renderer,
                                         (SlotId)vector_position,
                                         last_clicked_slot, socket_manager,
                                         left_click_event, right_click_event));
        }
    }
}

ItemButtonGrid::~ItemButtonGrid() {}

void ItemButtonGrid::handle_event(SDL_Event& e) {
    for (auto& button : buttons) {
        button.handle_event(e);
    }
}

int ItemButtonGrid::get_last_clicked_slot() {
    return last_clicked_slot;
}