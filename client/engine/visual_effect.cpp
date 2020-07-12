#include "visual_effect.h"

VisualEffect::VisualEffect(SDLSprite &sprite, visual_info_t visual_info)
    : RenderizableObject(visual_info), sprite(sprite) {}

void VisualEffect::render(SDL_Rect dest) { sprite.render(dest); }