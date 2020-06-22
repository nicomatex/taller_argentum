#ifndef __TEXT_INPUT_H
#define __TEXT_INPUT_H

#include <string>

#include "../SDL/sdl_text.h"
#include "../SDL/sdl_timer.h"
#include "SDL2/SDL_ttf.h"

class TextInput {
   private:
    std::string text;
    SDLText render_text;
    SDLTimer blink_timer;
    SDL_Renderer* renderer;
    SDL_Rect render_area;
    bool enabled;
    bool render_blink;
    void render_cursor();
    void render_background();
    SDL_Color background_color;

   public:
    TextInput(SDL_Rect render_area, const std::string& font_file,
              SDL_Renderer* renderer, SDL_Color font_color,
              SDL_Color background_color, TTF_Font* font);
    ~TextInput();
    /* Agrega caracteres al texto. */
    void add_characters(char* characters);

    /* Borra un caracter del texto. */
    void erase();

    /* Borra todo el texto escrito. */
    void erase_all();

    /* Renderiza el textbox. */
    void render();

    /* Devuelve el texto escrito en el input. */
    std::string get_text();

    /* Activa/desactiva el cursor. */
    void toggle();
};

#endif