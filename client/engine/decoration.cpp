#include "decoration.h"

Decoration::Decoration(SDLSprite sprite, int x, int y, int width, int height,
                       int x_offset, int y_offset)
    : RenderizableObject(width, height, x_offset, y_offset),
      sprite(sprite),
      x(x),
      y(y) {}

void Decoration::render(SDL_Rect dest) { sprite.render(dest); }

int Decoration::get_x() const { return x; }

int Decoration::get_y() const { return y; }