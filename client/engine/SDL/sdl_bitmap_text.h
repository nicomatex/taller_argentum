#ifndef __BITMAP_TEXT_H
#define __BITMAP_TEXT_H
#include "sdl_bitmap_font.h"

/**
 * @brief Clase de texto a partir de una fuente bitmap.
 * 
 */
class SDLBitmapText {
   private:
    SDLBitmapFont& font;
    std::string text;
    SDL_Color color;

   public:
    /**
     * @brief Crea un objeto SDLBitmapText
     * 
     * @param text Texto a mostrar.
     * @param font Fuente bitmap.
     * @param color Color del texto.
     */
    SDLBitmapText(const std::string& text, SDLBitmapFont& font,
                  SDL_Color color);
    ~SDLBitmapText();

    /**
     * @brief Renderiza el texto.
     * 
     * @param dest Destino en la pantalla donde se debe renderizar.
     */
    void render(SDL_Rect dest);

    /**
     * @brief Cambia el texto.
     * 
     * @param new_text Nuevo texto a mostrar
     */
    void update_text(const std::string& new_text);

    /**
     * @brief Devuelve la altura del texto.
     * 
     * @return int 
     */
    int get_height();
    
    /**
     * @brief Devuelve el ancho del texto.
     * 
     * @return int 
     */
    int get_width();

};

#endif