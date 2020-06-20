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
    /* Crea una textura renderizable que contiene el texto text, del color
     * indicado.*/
    SDLText(const std::string& text, const std::string& font_file,
            SDL_Color color, SDL_Renderer* renderer);

    /* No se permite construccion por copia*/
    SDLText(const SDLText& other) = delete;
    SDLText operator=(const SDLText& other) = delete;

    /* Constructor por movimiento.*/
    SDLText(SDLText&& other);
    SDLText& operator=(SDLText&& other);
    ~SDLText();

    /* Cambia el texto a renderizar al pasado por parametro. */
    void update_text(const std::string& text);
};

#endif
