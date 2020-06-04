#ifndef __SDL_TEXTURE_H
#define __SDL_TEXTURE_H
#include <cstdint>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "sdl_area.h"

class SDLTexture {
   protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width;
    int height;

   public:
    /* Usado para crear texturas sin color key. */
    SDLTexture(SDL_Renderer* renderer);

    SDLTexture(const std::string& filename, SDL_Renderer* renderer);

    /* Usado para crear texturas con un color key para transparencia. */
    SDLTexture(const std::string& filename, SDL_Renderer* renderer, uint8_t r,
               uint8_t g, uint8_t b);

    /* No se permite construccion por copia. */
    SDLTexture(const SDLTexture &other) = delete;
    SDLTexture operator=(const SDLTexture &other) = delete;
    
    /* Constructor por movimiento. */
    SDLTexture(SDLTexture &&other);
    SDLTexture& operator=(SDLTexture &&other);
    
    virtual ~SDLTexture();

    /* Renderiza la textura */
    void render(const SDLArea& src, const SDLArea& dest) const;
    void render(const SDLArea& dest) const;

    int get_width();
    int get_height();
};

#endif