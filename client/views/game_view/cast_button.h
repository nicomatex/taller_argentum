#ifndef __CAST_BUTTON_H
#define __CAST_BUTTON_H

#include "../../engine/UI/button.h"

class CastButton : public Button{

    public:
        CastButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer);

        void on_click() override;
};

#endif