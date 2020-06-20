#ifndef __TEXT_BOX_H
#define __TEXT_BOX_H
#include <deque>
#include <string>
#include <vector>

#include "../SDL/sdl_text.h"
#include "SDL2/SDL.h"

class TextBox {
   private:
    std::deque<std::string> lines;
    std::vector<SDLText> render_lines;
    SDL_Renderer* renderer;
    SDLArea render_area;
    void render_background();
    int nlines;
    SDL_Color background_color;

   public:
    TextBox(SDLArea render_area, const std::string& font_file,
            SDL_Renderer* renderer, int nlines, SDL_Color font_color,
            SDL_Color background_color);
    ~TextBox();
    void erase_all();
    void add_line(std::string string);
    void render();
};

#endif