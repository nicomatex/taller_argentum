#ifndef __BUTTON_H
#define __BUTTON_H

#include "SDL2/SDL.h"

class Button {
   private:
    SDL_Rect button_area;
    SDL_Rect viewport;
    SDL_Renderer* renderer;
    bool _button_clicked(int x,int y);

   public:
    Button(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer);
    virtual ~Button();

    void handle_event(SDL_Event& e);

    virtual void on_click() = 0;
};

#endif