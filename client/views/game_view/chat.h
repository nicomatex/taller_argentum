#ifndef __CHAT_H
#define __CHAT_H

#include "../../engine/UI/text_box.h"
#include "../../engine/UI/text_input.h"
#include "SDL2/SDL_ttf.h"

/**
 * @brief Chat del juego.
 * 
 */
class Chat {
   private:
    TextInput text_input;
    TextBox text_box;

   public:
    /**
     * @brief Crea un objeto Chat
     *
     * @param chat_area Area donde se va a renderizar el chat
     * @param nlines Cantidad de lineas de chat, una de las cuales se usa para
     * el text input.
     * @param renderer Renderer con el que se va a renderizar el chat.
     * @param font Fuente utilizada en la letra del chat.
     */
    Chat(SDL_Rect chat_area, int nlines, SDL_Renderer* renderer,
         TTF_Font* font);
    ~Chat();

    /**
     * @brief Agrega caracteres al input box del chat.
     *
     * @param characters Caracteres a agregar.
     */
    void add_characters(char* characters);

    /**
     * @brief Borra un caracter del input de texto.
     *
     */
    void input_erase();

    /* Devuelve el texto escrito en el input y deja el input en blanco.*/

    /**
     * @brief Devuelve el texto ingresado en el input, y lo borra.
     *
     * @return std::string
     */
    std::string get_input_and_erase();

    /**
     * @brief Imprime una linea en el chat.
     *
     * @param line Linea a imprimir.
     */
    void print_line(std::string line);

    /**
     * @brief Renderiza el chat.
     *
     */
    void render();

    /**
     * @brief Activa / desactiva el cursor del chat.
     *
     */
    void toggle();
};

#endif