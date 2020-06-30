#ifndef __CHAT_H
#define __CHAT_H

#include "SDL2/SDL_ttf.h"
#include "../engine/UI/text_box.h"
#include "../engine/UI/text_input.h"

class Chat {
   private:
    TextInput text_input;
    TextBox text_box;

   public:
    /* La altura del area pasada por parametro sera dividida entre las n lineas,
    una de las cuales se utilizara para la entrada de texto, y las otras
    n - 1 para mostrar los mensajes del chat. */
    Chat(SDL_Rect chat_area, int nlines, SDL_Renderer* renderer,
         TTF_Font* font);
    ~Chat();

    /* Agrega caracteres al input box del chat. */
    void add_characters(char* characters);

    /* Borra un caracter del input de texto.*/
    void input_erase();

    /* Devuelve el texto escrito en el input y deja el input en blanco.*/
    std::string get_input_and_erase();

    /* Imprime una nueva linea en el chat. */
    void print_line(std::string line);

    /* Renderiza el chat. */
    void render();

    /* Activa/desactiva el cursor. */
    void toggle();
};

#endif