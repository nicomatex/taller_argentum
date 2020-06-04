#include "sdl_window.h"

bool debug = true;

int main(void){
    SDLWindow ventana(800,600);
    SDL_Renderer* renderer = ventana.init_renderer();
    SDLTexture sprite_texture("sprite.png",renderer,0,0,0);
    SDLSprite caminando_abajo(sprite_texture,6,14,0,0,56,100);
    SDLSprite caminando_derecha(sprite_texture,5,10,0,200,56,100);
    SDLArea area_renderizado_abajo(10,10,64,128);
    SDLArea area_renderizado_derecha(70,10,64,128);
    bool running = true;

    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
            }
        }
        ventana.fill(0,200,100,255);
        caminando_abajo.render(area_renderizado_abajo);
        caminando_derecha.render(area_renderizado_derecha);
        ventana.render();
    }
    return 0;
}