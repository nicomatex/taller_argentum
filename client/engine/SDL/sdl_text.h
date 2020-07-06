#ifndef __SDL_TEXT_H
#define __SDL_TEXT_H

#include <cstdint>

#include "SDL2/SDL_ttf.h"
#include "sdl_texture.h"

class SDLText : public SDLTexture {
   private:
    TTF_Font* font;
    SDL_Color text_color;

   public:
    /**
     * @brief Crea un objeto SDLText
     *
     * @param text Texto a renderizar.
     * @param font Fuente a utilizar para el texto.
     * @param color Color del texto.
     * @param renderer Renderer al cual se asociara la textura del texto.
     */
    SDLText(const std::string& text, TTF_Font* font, SDL_Color color,
            SDL_Renderer* renderer);

    /* No se permite construccion por copia*/
    SDLText(const SDLText& other) = delete;
    SDLText operator=(const SDLText& other) = delete;

    /* Constructor por movimiento.*/
    SDLText(SDLText&& other);
    SDLText& operator=(SDLText&& other);
    ~SDLText();

    /**
     * @brief Cambia el texto a renderizar
     *
     * @param text Nuevo texto a renderizar.
     */
    void update_text(const std::string& text);
};

#endif
