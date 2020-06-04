#ifndef __SDL_WINDOW_H
#define __SDL_WINDOW_H

#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "sdl_animated_sprite.h"
#include "sdl_text.h"
#include "sdl_texture.h"

class SDLWindow {
   private:
    SDL_Window *window;
    SDL_Renderer *renderer;

   public:
    /* Constructor. Recibe ancho y alto de la ventana en pixeles. */
    SDLWindow(int width, int height);
    ~SDLWindow();

    /* Llena toda la ventana con el color indicado en los parametros. */
    void fill(int r, int g, int b, int alpha);

    /* Renderiza la ventana con todos sus contenidos.*/
    void render() const;

    /* Inicializa el renderer de la ventana, y devuelve un puntero al mismo.*/
    SDL_Renderer* init_renderer();
};

#endif