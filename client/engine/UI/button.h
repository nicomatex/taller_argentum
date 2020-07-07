#ifndef __BUTTON_H
#define __BUTTON_H

#include "SDL2/SDL.h"

/**
 * @brief Boton abstracto. Todos los botones heredan de esta clase.
 * 
 */
class Button {
   private:
    SDL_Rect button_area;
    SDL_Rect viewport;
    SDL_Renderer* renderer;
    bool _button_clicked(int x, int y);

   public:
    /**
     * @brief Crea un objeto Button
     *
     * @param button_area Area de accion del boton.
     * @param viewport Viewport que contiene al boton.Utilizado para la
     * deteccion de clics.
     * @param renderer Renderer asociado al boton.(Para botones invisibles no es
     * necesario. Se puede pasar NULL.)
     */
    Button(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer);
    virtual ~Button();

    /**
     * @brief Analiza si se trata de un click en el boton, y de ser asi llama a
     * on_click().
     *
     * @param e Evento de SDL.
     */
    void handle_event(SDL_Event& e);

    /**
     * @brief Accion a ejecutar cuando se clickea el boton izquierdo.
     *
     */
    virtual void on_click();

    /**
     * @brief Accion a ejecutar cuando se clickea el boton derecho.
     * 
     */
    virtual void on_right_click();
};

#endif