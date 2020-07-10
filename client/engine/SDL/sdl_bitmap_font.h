#ifndef __BITMAP_FONT
#define __BITMAP_FONT
#include "sdl_texture.h"

/**
 * @brief Fuente bitmap.
 * 
 */
class SDLBitmapFont {
   private:
    SDLTexture& font_texture;
    int first_ascii_char;
    int char_width;
    int char_height;
    int chars_per_row;
    
   public:
    /**
     * @brief Crea un objeto SDLBitmapFont
     * 
     * @param font_texture Textura base de la fuente.
     * @param first_ascii_char Primer caracter ascii que muestra el texto.
     * @param char_width Ancho de cada caracter.
     * @param char_height Alto de cada caracter.
     * @param chars_per_row Cantidad de caracteres por fila.
     */
    SDLBitmapFont(SDLTexture& font_texture, int first_ascii_char,
               int char_width, int char_height, int chars_per_row);
    ~SDLBitmapFont();

    /**
     * @brief Renderiza un caracter
     * 
     * @param ascii_char Valor ascii del caracter a renderizar.
     * @param dest Destino en la pantalla donde se va a renderizar el caracter.
     */
    void render_character(int ascii_char, SDL_Rect dest);

    /**
     * @brief Devuelve la altura de un caracter.
     * 
     * @return int 
     */
    int get_char_height();

    /**
     * @brief Devuelve el ancho de un caracter.
     * 
     * @return int 
     */
    int get_char_width();

    /**
     * @brief Cambia el color de la fuente.
     * 
     * @param r Rojo
     * @param g Verde
     * @param b Azul
     */
    void set_color(uint8_t r,uint8_t g,uint8_t b);

    /**
     * @brief Resetea el color al default de la fuente.
     * 
     */
    void reset_color();

};

#endif