#ifndef __DECORATION_H
#define __DECORATION_H

#include "SDL/sdl_animated_sprite.h"
#include "renderizable_object.h"

class Decoration : public RenderizableObject {
   private:
    SDLSprite sprite;
    int x,y;

   public:
    Decoration(SDLSprite sprite,int x,int y, int width, int height,
               int x_offset, int y_offset);
    /* Renderiza el objeto en pantalla. */
    int get_x() const;
    int get_y() const;
    void render(SDL_Rect dest) override;
};

#endif
