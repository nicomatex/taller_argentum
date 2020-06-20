#ifndef __SDL_WINDOW_H
#define __SDL_WINDOW_H

#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "sdl_animated_sprite.h"
#include "sdl_text.h"
#include "sdl_texture.h"
#include "sdl_area.h"

class SDLWindow {
   private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;

   public:
    /* Constructor. Recibe ancho y alto de la ventana en pixeles. */
    SDLWindow(int width, int height,const std::string &title);
    ~SDLWindow();

    /* Llena toda la ventana con el color indicado en los parametros. */
    void fill(int r, int g, int b, int alpha);

    /* Renderiza la ventana con todos sus contenidos.*/
    void render() const;

    /* Setea el viewport del renderer absoluto en la ventana. */
    void set_viewport(const SDLArea &viewport_area);

    /* Inicializa el renderer de la ventana, y devuelve un puntero al mismo.*/
    SDL_Renderer* init_renderer();

    SDL_Renderer* get_renderer();
    
    int get_width() const;
    int get_height() const;
};

#endif