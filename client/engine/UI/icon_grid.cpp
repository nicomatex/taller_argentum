#include "icon_grid.h"

#include <iostream>
#include <stdexcept>
IconGrid::IconGrid(SDL_Rect render_area, SDL_Renderer* renderer, int rows,
                   int cols)
    : render_area(render_area),
      renderer(renderer),
      icon_width(render_area.w / cols),
      icon_height(render_area.h / rows),
      rows(rows),
      cols(cols) {
    icons.resize(rows * cols);
    for (int i = 0; i < icons.size(); i++) {
        icons[i] = NULL;
    }
}

IconGrid::~IconGrid() {}

void IconGrid::set_icon(int position, SDLTexture* icon) {
    if (position > icons.size()) {
        throw std::out_of_range("Invalid position");
    }
    icons[position] = icon;
}

void IconGrid::render() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int vector_position = j + i * cols;
            if (!icons[vector_position]) continue;

            SDL_Rect dest_area = {render_area.x + j * icon_width,
                                  render_area.y + i * icon_height, 
                                  icon_width,
                                  icon_height};
            icons[vector_position]->render(dest_area);
        }
    }
}