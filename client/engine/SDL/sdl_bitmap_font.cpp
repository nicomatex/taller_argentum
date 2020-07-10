#include "sdl_bitmap_font.h"

SDLBitmapFont::SDLBitmapFont(SDLTexture& font_texture, int first_ascii_char,
                             int char_width, int char_height, int chars_per_row)
    : font_texture(font_texture),
      first_ascii_char(first_ascii_char),
      char_width(char_width),
      char_height(char_height),
      chars_per_row(chars_per_row) {}

SDLBitmapFont::~SDLBitmapFont() {}

void SDLBitmapFont::render_character(int ascii_char, SDL_Rect dest) {
    int relative_char = ascii_char - first_ascii_char;
    if (relative_char < 0) return;

    int row = relative_char / chars_per_row;
    int col = relative_char % chars_per_row;
    SDL_Rect src = {col * char_width, row * char_height, char_width,
                    char_height};
    font_texture.render(src, dest);
}

int SDLBitmapFont::get_char_width() { return char_width; }

int SDLBitmapFont::get_char_height() { return char_height; }

void SDLBitmapFont::set_color(uint8_t r,uint8_t g,uint8_t b){
  font_texture.set_color_mod(r,g,b);
}

void SDLBitmapFont::reset_color(){
  font_texture.reset_color_mod();
}