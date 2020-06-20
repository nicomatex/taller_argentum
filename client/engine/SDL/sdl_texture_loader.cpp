#include "sdl_texture_loader.h"

SDLTextureLoader::SDLTextureLoader(SDL_Renderer *renderer)
    : renderer(renderer) {}

SDLTextureLoader::~SDLTextureLoader(){}

SDLTexture SDLTextureLoader::load_texture(const std::string &filename) const {
    return SDLTexture(filename, renderer);
}

SDLTexture SDLTextureLoader::load_texture(const std::string &filename, int r,
                                          int g, int b) const {
    return SDLTexture(filename,renderer,r,g,b);
}