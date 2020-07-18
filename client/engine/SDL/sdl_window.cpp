#include "sdl_window.h"

#include <iostream>

#include "SDL2/SDL_ttf.h"
#include "sdl_config.h"
#include "sdl_error.h"
#include "sdl_text.h"

SDLWindow::SDLWindow(int width, int height, const std::string &title,
                     bool fullscreen, bool vsync):vsync(vsync) {
    int errCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (errCode < 0) {
        throw SDLError(ERR_SDL_INIT);
    }
    errCode = IMG_Init(IMG_INIT_PNG);
    if (errCode == 0) {
        throw SDLError(ERR_IMAGE_INIT);
    }
    if (TTF_Init() == -1) {
        throw SDLError(ERR_TTF_INIT);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw SDLError(ERR_MIXER_INIT);
    }

    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    this->window =
        SDL_CreateWindow(title.c_str(), 100, 100, width, height, flags);
    if (!this->window) {
        throw SDLError(ERR_WINDOW_INIT);
    }

}

SDL_Renderer *SDLWindow::init_renderer() {
    uint32_t flags = SDL_RENDERER_ACCELERATED;
    if(vsync) flags |= SDL_RENDERER_PRESENTVSYNC;

    this->renderer = SDL_CreateRenderer(
        this->window, -1, flags);
    if (!this->renderer) {
        SDL_DestroyWindow(this->window);
        throw SDLError(ERR_RENDERER_INIT);
    }
    return this->renderer;
}

SDLWindow::~SDLWindow() {
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
    Mix_Quit();
}

void SDLWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SDLWindow::set_viewport(SDL_Rect viewport_area) {
    SDL_RenderSetViewport(this->renderer, &viewport_area);
}

void SDLWindow::reset_viewport() {
    SDL_RenderSetViewport(this->renderer, NULL);
}

void SDLWindow::render() const { SDL_RenderPresent(renderer); }

int SDLWindow::get_height() const {
    int height;
    SDL_GetWindowSize(this->window, NULL, &height);
    return height;
}

int SDLWindow::get_width() const {
    int width;
    SDL_GetWindowSize(this->window, &width, NULL);
    return width;
}

SDL_Renderer *SDLWindow::get_renderer() { return renderer; }

void SDLWindow::hide() { SDL_HideWindow(this->window); }

void SDLWindow::show() { SDL_ShowWindow(this->window); }