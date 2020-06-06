#include "decoration.h"

Decoration::Decoration(SDLSprite sprite, int x, int y, int width, int height)
    : VisualComponent(x, y, width, height), sprite(sprite) {}

void Decoration::render(const SDLArea &dest){
    sprite.render(dest);
}
