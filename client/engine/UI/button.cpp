#include "button.h"

Button::Button(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer)
    : button_area(button_area), viewport(viewport), renderer(renderer) {}

Button::~Button() {}

bool Button::_button_clicked(int x, int y) {
    int relative_x = x - viewport.x;
    int relative_y = y - viewport.y;

    if (relative_x < button_area.x ||
        relative_x > button_area.x + button_area.w)
        return false;

    if (relative_y < button_area.y ||
        relative_y > button_area.y + button_area.h)
        return false;
    
    return true;
}

void Button::handle_event(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(_button_clicked(x,y)){
            if(e.button.button == SDL_BUTTON_LEFT) on_click();
            if(e.button.button == SDL_BUTTON_RIGHT) on_right_click();
        }
    }
}

void Button::on_click(){}

void Button::on_right_click(){}