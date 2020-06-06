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

SDLText SDLTextureLoader::load_text(const std::string &text, const std::string &font_file,
                         int r, int g, int b) const{
    return SDLText(text,font_file,r,g,b,renderer);
}