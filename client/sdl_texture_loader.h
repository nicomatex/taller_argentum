#ifndef __TEXTURE_LOADER_H
#define __TEXTURE_LOADER_H
#include "SDL2/SDL.h"
#include "sdl_texture.h"
#include "sdl_text.h"

class SDLTextureLoader {
   private:
    SDL_Renderer *renderer;

   public:
    SDLTextureLoader(SDL_Renderer *renderer);
    ~SDLTextureLoader();

    SDLTexture load_texture(const std::string &filename) const;
    SDLTexture load_texture(const std::string &filename, int r, int g, int b) const;
    SDLText load_text(const std::string &text, const std::string &font_file,
                         int r, int g, int b) const;
};

#endif