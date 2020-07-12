#ifndef __VISUAL_EFFECT_H
#define __VISUAL_EFFECT_H
#include "renderizable_object.h"

class VisualEffect: public RenderizableObject{
    private:
        SDLSprite sprite;

    public:
        VisualEffect(SDLSprite &sprite, visual_info_t visual_info);

        void render(SDL_Rect dest) override;
};


#endif