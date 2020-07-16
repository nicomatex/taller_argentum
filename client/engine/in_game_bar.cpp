#include "in_game_bar.h"

InGameBar::InGameBar(visual_info_t visual_info, SDL_Color color)
    : RenderizableObject(visual_info), color(color), bar_texture() {}
