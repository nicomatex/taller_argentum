#include "sdl_window.h"
#include "sdl_texture_loader.h"
#include <vector>
#include <iostream>

bool debug = true;
#define TILE_SIZE 64
int main(void){
    SDLWindow ventana(800,600);
    SDLTextureLoader loader(ventana.init_renderer());

    SDLTexture sprite_texture = loader.load_texture("sprite.png",0,0,0);
    SDLTexture floor_texture = loader.load_texture("piso1.png");

    SDLSprite caminando_abajo(sprite_texture,6,14,0,0,56,100);

    SDLArea mapa[15][20];

    for(int fila = 0;fila < 10;fila++){
        for(int columna = 0;columna < 23;columna++){
            mapa[fila][columna].set_new_size(TILE_SIZE,TILE_SIZE);
            mapa[fila][columna].set_new_pos((columna*TILE_SIZE),(fila*TILE_SIZE));
        }
    }

    SDLArea area_renderizado_abajo(TILE_SIZE/2,TILE_SIZE/2,TILE_SIZE/2,TILE_SIZE);
    bool running = true;

    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
            }
        }
        ventana.fill(0,200,100,255);

        for(int fila = 0;fila < 15;fila++){
            for(int columna = 0;columna < 20;columna++){
                floor_texture.render(mapa[fila][columna]);
                std::cout << fila << "-" << columna << std::endl;
            }
        }
        caminando_abajo.render(area_renderizado_abajo);
        ventana.render();
    }
    return 0;
}