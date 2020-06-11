#ifndef __DECORATION_H
#define __DECORATION_H

#include "SDL/sdl_animated_sprite.h"
#include "renderizable_object.h"

class Decoration : public RenderizableObject {
   private:
    SDLSprite sprite;

   public:
    Decoration(SDLSprite sprite, int x, int y, int width, int height,
               int x_offset, int y_offset);
    /* Renderiza el objeto en pantalla. */
    void render(const SDLArea &dest) override;
};

#endif
