#ifndef __TEXT_BOX_H
#define __TEXT_BOX_H
#include <deque>
#include <string>
#include <vector>

#include "../SDL/sdl_text.h"
#include "SDL2/SDL.h"

/**
 * @brief Caja de texto. Usada en el chat.
 * 
 */
class TextBox {
   private:
    std::deque<std::string> lines;
    std::vector<SDLText> render_lines;
    SDL_Rect render_area;
    SDL_Renderer* renderer;
    int nlines;
    SDL_Color background_color;
    void render_background();

   public:
   /**
    * @brief Crea un objeto TextBox
    * 
    * @param render_area Area donde se va a renderizar el textbox.
    * @param renderer Renderer con el cual se va a renderizar el textbox.
    * @param nlines Cantidad de lineas del textbox.
    * @param font_color Color del texto.
    * @param background_color Color de fondo.
    * @param font Fuente tipografica del texto.
    */
    TextBox(SDL_Rect render_area, SDL_Renderer* renderer, int nlines,
            SDL_Color font_color, SDL_Color background_color, TTF_Font* font);
    ~TextBox();

    /**
     * @brief Borra todo el texto del textbox.
     * 
     */
    void erase_all();

    /**
     * @brief Agrega una nueva linea al textbox.
     * 
     * @param string Linea a agregar.
     */
    void add_line(std::string string);

    /**
     * @brief Renderiza el textbox.
     * 
     */
    void render();
};

#endif