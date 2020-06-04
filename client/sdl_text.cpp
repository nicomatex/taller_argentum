#include "sdl_text.h"

#include "SDL2/SDL_ttf.h"
#include "sdl_config.h"
#include "sdl_error.h"

SDLText::SDLText(const std::string& text, const std::string& font_file,
                 uint8_t r, uint8_t g, uint8_t b, SDL_Renderer* renderer)
    : SDLTexture(renderer) {
    font = TTF_OpenFont(font_file.c_str(), 28);

    if (!font) {
        throw SDLError(ERR_TEXT_FONT);
    }

    text_color = {r, g, b};
    update_text(text);
}

SDLText::SDLText(SDLText&& other) : SDLTexture(std::move(other)) {
    this->font = std::move(other.font);
}

SDLText& SDLText::operator=(SDLText&& other) {
    SDLTexture::operator=(std::move(other));
    this->font = std::move(other.font);
    return *this;
}

SDLText::~SDLText() { TTF_CloseFont(font); }

void SDLText::update_text(const std::string& text) {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(font, text.c_str(), text_color);
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