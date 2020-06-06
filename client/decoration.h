#ifndef __DECORATION_H
#define __DECORATION_H

#include "visual_component.h"
#include "include/SDL/sdl_animated_sprite.h"

class Decoration : public VisualComponent {
   private:
    SDLSprite sprite;

   public:
    Decoration(SDLSprite sprite, int x, int y, int width, int height);
    /* Renderiza el objeto en pantalla. */
    void render(const SDLArea &dest) override;
};

#endif
