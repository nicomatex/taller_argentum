#include "sdl_bitmap_text.h"

SDLBitmapText::SDLBitmapText(const std::string& text, SDLBitmapFont& font,
                             SDL_Color color)
    : font(font), text(text), color(color) {}

SDLBitmapText::~SDLBitmapText(){}

void SDLBitmapText::render(SDL_Rect dest){
    if(text.size() == 0) return;
    int char_height = dest.h;
    int char_width = dest.w / text.size();
    font.set_color(color.r,color.g,color.b);
    for(int i = 0; i < (int)text.size();i++){
        SDL_Rect char_dest = {dest.x + (i*char_width)/2, dest.y, char_width, char_height};
        int ascii_character = (int)text[i];
        font.render_character(ascii_character,char_dest);
    }
    font.reset_color();
}

void SDLBitmapText::update_text(const std::string& new_text){
    text = new_text;
}

int SDLBitmapText::get_height(){
    return font.get_char_height();
}

int SDLBitmapText::get_width(){
    return font.get_char_width() * text.size();
}