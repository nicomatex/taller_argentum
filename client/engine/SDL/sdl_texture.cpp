#include "sdl_texture.h"

#include "sdl_config.h"
#include "sdl_error.h"

SDLTexture::SDLTexture(SDL_Renderer* renderer)
    : renderer(renderer), texture(nullptr) {}

SDLTexture::SDLTexture(const std::string& filename, SDL_Renderer* renderer)
    : renderer(renderer) {
    this->texture = IMG_LoadTexture(this->renderer, filename.c_str());

    if (!this->texture) {
        throw SDLError(ERR_TEX_LOAD);
    }

    int query_result = (SDL_QueryTexture(this->texture, NULL, NULL,
                                         &(this->width), &(this->height)) < 0);
    if (query_result < 0) {
        throw SDLError(ERR_TEX_DIMENSIONS);
    }
}

SDLTexture::SDLTexture(const std::string& filename, SDL_Renderer* renderer,
                       uint8_t r, uint8_t g, uint8_t b)
    : renderer(renderer) {
    SDL_Surface* loaded_surface = IMG_Load(filename.c_str());
    if (!loaded_surface) {
        throw SDLError(ERR_TEX_LOAD);
    }

    int key_result = SDL_SetColorKey(
        loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, r, g, b));

    if (key_result < 0) {
        SDL_FreeSurface(loaded_surface);
        throw SDLError(ERR_TEX_CKEY);
    }

    this->texture =
        SDL_CreateTextureFromSurface(this->renderer, loaded_surface);

    if (!this->texture) {
        throw SDLError(ERR_TEX_CKEY_CREATE);
    }

    this->width = loaded_surface->w;
    this->height = loaded_surface->h;

    SDL_FreeSurface(loaded_surface);
}

SDLTexture::SDLTexture(SDLTexture&& other) {
    this->texture = std::move(other.texture);
    this->renderer = std::move(other.renderer);
    this->height = std::move(other.height);
    this->width = std::move(other.width);
    other.texture = nullptr;
    other.renderer = nullptr;
    other.height = 0;
    other.width = 0;
}

SDLTexture& SDLTexture::operator=(SDLTexture&& other) {
    this->texture = std::move(other.texture);
    this->renderer = std::move(other.renderer);
    this->height = std::move(other.height);
    this->width = std::move(other.width);
    other.texture = nullptr;
    other.renderer = nullptr;
    other.height = 0;
    other.width = 0;
    return *this;
}

SDLTexture::~SDLTexture() {
    if (this->texture) SDL_DestroyTexture(this->texture);
}

void SDLTexture::render(const SDLArea& src, const SDLArea& dest) const {
    SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};

    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                        dest.getHeight()};

    int render_result =
        SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
    if (render_result < 0) {
        throw SDLError(ERR_TEX_RENDER);
    }
}

void SDLTexture::render(const SDLArea& dest) const {
    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                        dest.getHeight()};

    int render_result =
        SDL_RenderCopy(this->renderer, this->texture, NULL, &sdlDest);
    if (render_result < 0) {
        throw SDLError(ERR_TEX_RENDER);
    }
}

int SDLTexture::get_height() const { return this->height; }

int SDLTexture::get_width() const { return this->width; }