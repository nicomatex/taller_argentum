#include "icon_grid.h"

#include <iostream>
#include <stdexcept>
IconGrid::IconGrid(SDL_Rect render_area, SDL_Renderer* renderer, int rows,
                   int cols, float size_proportion, bool original_proportions)
    : render_area(render_area),
      renderer(renderer),
      icon_width(render_area.w / cols),
      icon_height(render_area.h / rows),
      rows(rows),
      cols(cols),
      size_proportion(size_proportion),
      original_proportions(original_proportions) {
    icons.resize(rows * cols);
    for (int i = 0; i < icons.size(); i++) {
        icons[i] = NULL;
    }
    if (size_proportion < 0) size_proportion = 0;
    if (size_proportion > 1) size_proportion = 1;
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
                                  (int)(icon_width * size_proportion),
                                  (int)(icon_height * size_proportion)};
            if (original_proportions) {
                float scale_factor =
                    (float)dest_area.h /
                    (float)icons[vector_position]->get_height();
                dest_area.w =
                    (float)icons[vector_position]->get_width() * scale_factor;
            }
            icons[vector_position]->render(dest_area);
        }
    }
}