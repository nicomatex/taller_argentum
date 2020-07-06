#ifndef __SDL_WINDOW_H
#define __SDL_WINDOW_H

#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "sdl_animated_sprite.h"
#include "sdl_text.h"
#include "sdl_texture.h"

class SDLWindow {
   private:
    SDL_Window *window;
    SDL_Renderer *renderer;

   public:
    /* Constructor. Recibe ancho y alto de la ventana en pixeles. */

    /**
     * @brief Crea un objeto SDLWindow
     *
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     * @param title Titulo de la ventana.
     * @param fullscreen Si es true, la ventana se creara fullscreen, utilizando
     * como dimensiones la resolucion actual.
     */
    SDLWindow(int width, int height, const std::string &title, bool fullscreen);
    ~SDLWindow();

    /* Llena toda la ventana con el color indicado en los parametros. */
    /**
     * @brief Limpia la ventana, y la pinta de un color.
     *
     * @param r Rojo de renderizado.
     * @param g Verde de renderizado.
     * @param b Azul de renderizado.
     * @param alpha Alpha de renderizado.
     */
    void fill(int r, int g, int b, int alpha);

    /* Renderiza la ventana con todos sus contenidos.*/
    /**
     * @brief Renderiza todos los contenidos cargados en el buffer de
     * renderizado.
     *
     */
    void render() const;

    /**
     * @brief Setea el viewport del renderer.
     * 
     * @param viewport_area Area que sera el viewport nuevo.
     */
    void set_viewport(SDL_Rect viewport_area);

    /**
     * @brief Restaura el viewport a la totalidad de la ventana.
     * 
     */
    void reset_viewport();

    /**
     * @brief Inicia el renderer de la ventana.
     * 
     * @return SDL_Renderer* 
     */
    SDL_Renderer *init_renderer();

    /**
     * @brief Devuelve el renderer asociado a la ventana.
     * 
     * @return SDL_Renderer* 
     */
    SDL_Renderer *get_renderer();

    /**
     * @brief Devuelve el ancho de la ventana.
     * 
     * @return int 
     */
    int get_width() const;

    /**
     * @brief Devuelve el alto de la ventana.
     * 
     * @return int 
     */
    int get_height() const;

    /**
     * @brief Oculta la ventana.
     * 
     */
    void hide();

    /**
     * @brief Muestra la ventana.
     * 
     */
    void show();
};

#endif