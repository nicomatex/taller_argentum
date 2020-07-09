#ifndef __TEXT_INPUT_H
#define __TEXT_INPUT_H

#include <string>

#include "../SDL/sdl_text.h"
#include "../SDL/sdl_timer.h"
#include "SDL2/SDL_ttf.h"

/**
 * @brief Input de texto.
 *
 */
class TextInput {
   private:
    std::string text;
    uint64_t max_len;
    SDLText render_text;
    SDLTimer blink_timer;
    SDL_Renderer* renderer;
    SDL_Rect render_area;
    bool enabled;
    bool render_blink;
    void render_cursor();
    void render_background();
    SDL_Color background_color;

   public:
    /**
     * @brief Crea un objeto TextInput
     *
     * @param render_area Area de la pantalla donde se va a renderizar el
     * input.
     * @param renderer Renderer con el cual se renderizara el input.
     * @param font_color Color del texto.
     * @param background_color Color del fondo del input.
     * @param font Fuente tipografica del texto.
     */
    TextInput(SDL_Rect render_area, SDL_Renderer* renderer,
              SDL_Color font_color, SDL_Color background_color, TTF_Font* font,
              uint64_t max_len = UINT64_MAX);
    ~TextInput();

    /**
     * @brief Agrega caracteres al texto.
     *
     * @param characters Caracteres a agregar.
     */
    void add_characters(char* characters);

    /**
     * @brief Borra un caracter del texto.
     * @details Si el texto esta vacio, no hace nada.
     */
    void erase();

    /**
     * @brief Borra todo el texto escrito.
     *
     */
    void erase_all();

    /**
     * @brief Renderiza el textbox y todo su texto.
     *
     */
    void render();

    /**
     * @brief Devuelve el texto escrito.
     *
     * @return std::string
     */
    std::string get_text();

    /**
     * @brief Activa/desactiva el cursor.
     *
     */
    void toggle();
};

#endif