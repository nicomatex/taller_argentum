#include "decoration.h"

Decoration::Decoration(SDLSprite sprite, int x, int y, visual_info_t visual_info)
    : RenderizableObject(visual_info),
      sprite(sprite),
      x(x),
      y(y) {}

void Decoration::render(SDL_Rect dest) { sprite.render(dest); }

int Decoration::get_x() const { return x; }

int Decoration::get_y() const { return y; }