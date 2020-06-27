#include "sdl_text.h"

#include <iostream>

#include "SDL2/SDL_ttf.h"
#include "sdl_config.h"
#include "sdl_error.h"
SDLText::SDLText(const std::string& text, TTF_Font* font, SDL_Color color,
                 SDL_Renderer* renderer)
    : SDLTexture(renderer),
      text_color(color),
      font(font),
      style(TTF_STYLE_NORMAL) {
    if (!font) {
        throw SDLError(ERR_TEXT_FONT);
    }
    update_text(text);
}

SDLText::SDLText(SDLText&& other) : SDLTexture(std::move(other)) {
    this->font = std::move(other.font);
    this->text_color = std::move(other.text_color);
    other.font = NULL;
}

SDLText& SDLText::operator=(SDLText&& other) {
    SDLTexture::operator=(std::move(other));
    this->font = std::move(other.font);
    this->text_color = std::move(other.text_color);
    other.font = NULL;
    return *this;
}

SDLText::~SDLText() {}

void SDLText::update_text(const std::string& text) {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }

    std::string render_text;
    if (text.size() == 0) {
        render_text = " ";
    } else {
        render_text = text;
    }
    TTF_SetFontStyle(font,style);
    SDL_Surface* text_surface =
        TTF_RenderText_Blended(font, render_text.c_str(), text_color);
    if (!text_surface) {
        throw SDLError(ERR_TEXT_CREATE);
    }

    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!texture) {
        throw SDLError(ERR_TEXT_CREATE);
    }
    width = text_surface->w;
    height = text_surface->h;
    SDL_FreeSurface(text_surface);
}


void SDLText::set_style(int new_style){
    style = new_style;
}