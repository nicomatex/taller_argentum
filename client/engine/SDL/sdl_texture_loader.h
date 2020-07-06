#ifndef __TEXTURE_LOADER_H
#define __TEXTURE_LOADER_H
#include "SDL2/SDL.h"
#include "sdl_text.h"
#include "sdl_texture.h"

class SDLTextureLoader {
   private:
    SDL_Renderer *renderer;

   public:
    /**
     * @brief Crea un objeto SDLTextureLoader
     *
     * @param renderer Renderer al cual se asocian las texturas creadas.
     */
    SDLTextureLoader(SDL_Renderer *renderer);
    ~SDLTextureLoader();

    /**
     * @brief Carga una textura.
     *
     * @param filename Ruta al archivo a partir del cual se generara la textura.
     * @return SDLTexture
     */
    SDLTexture load_texture(const std::string &filename) const;

    /**
     * @brief Carga una textura.
     * @details Se tomara como transparencia el color key indicado con los
     * parametros r,g,b.
     *
     * @param filename Ruta al archivo a partir del cual se generara la textura.
     * @param r Color rojo del color key.
     * @param g Verde del color key.
     * @param b Azul del color key.
     * @return SDLTexture
     */
    SDLTexture load_texture(const std::string &filename, int r, int g,
                            int b) const;
    SDLText load_text(const std::string &text, const std::string &font_file,
                      int r, int g, int b) const;
};

#endif