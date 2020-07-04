#include "item_button_grid.h"

ItemButtonGrid::ItemButtonGrid(SDL_Rect inventory_area, SDL_Rect viewport,
                               SDL_Renderer* renderer, int rows, int cols,
                               SocketManager& socket_manager) {
    int button_width = inventory_area.w / cols;
    int button_height = inventory_area.h / rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int vector_position = j + i * cols;
            SDL_Rect button_area = {inventory_area.x + j * button_width,
                                    inventory_area.y + i * button_height,
                                    button_width, button_height};
            buttons.push_back(ItemButton(button_area, viewport, renderer,
                                         (SlotId)vector_position, socket_manager));
        }
    }
}

ItemButtonGrid::~ItemButtonGrid() {}

void ItemButtonGrid::handle_event(SDL_Event& e) {
    for (auto& button : buttons) {
        button.handle_event(e);
    }
}