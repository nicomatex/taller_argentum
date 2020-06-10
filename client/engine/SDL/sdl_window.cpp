#include <iostream>
#include "SDL2/SDL_ttf.h"

#include "sdl_config.h"
#include "sdl_window.h"
#include "sdl_error.h"
#include "sdl_text.h"

extern bool debug;

SDLWindow::SDLWindow(int width, int height,const std::string &title) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SDLError(ERR_SDL_INIT);
    }
    errCode = IMG_Init(IMG_INIT_PNG);
    if (errCode == 0) {
        throw SDLError(ERR_IMAGE_INIT);
    }
    if (TTF_Init() == -1) {
        throw SDLError(ERR_TTF_INIT);
    }
    if (debug)
        std::cout << "[DEBUG] SDL, IMAGE y TTF inicializados." << std::endl;

    this->window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, 0);
    if (!this->window) {
        throw SDLError(ERR_WINDOW_INIT);
    }

    if(debug)
        std::cout << "[DEBUG] Ventana creada." << std::endl;
}

SDL_Renderer* SDLWindow::init_renderer(){
    this->renderer = SDL_CreateRenderer(
        this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        SDL_DestroyWindow(this->window);
        throw SDLError(ERR_RENDERER_INIT);
    }
    if(debug)
        std::cout << "[DEBUG] Renderer inicializado." << std::endl;
    return this->renderer;
}

SDLWindow::~SDLWindow() {
    if(debug)
        std::cout << ("[DEBUG] Destruyendo ventana.") << std::endl;
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDLWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SDLWindow::render() const{ SDL_RenderPresent(renderer); }