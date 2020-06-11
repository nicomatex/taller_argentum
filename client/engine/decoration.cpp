#include "decoration.h"

Decoration::Decoration(SDLSprite sprite, int x, int y, int width, int height,
                       int x_offset, int y_offset)
    : RenderizableObject(x,y,width, height, x_offset, y_offset), sprite(sprite) {}

void Decoration::render(const SDLArea &dest) { sprite.render(dest); }