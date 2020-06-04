#include <iostream>
#include <vector>

#include "include/SDL/sdl_texture_loader.h"
#include "include/SDL/sdl_window.h"
#include "visual_component.h"

bool debug = true;

#define TILE_SIZE 64

VisualComponent load_component(SDLTexture &texture) {
    SDLSprite right_idle(texture, 1, 1, 0, 300, 56, 100);
    SDLSprite left_idle(texture, 1, 1, 0, 200, 56, 100);
    SDLSprite up_idle(texture, 1, 1, 0, 100, 56, 100);
    SDLSprite down_idle(texture, 1, 1, 0, 0, 56, 100);

    SDLSprite right_move(texture, 5, 10, 0, 300, 56, 100);
    SDLSprite left_move(texture, 5, 10, 0, 200, 56, 100);
    SDLSprite up_move(texture, 6, 10, 0, 100, 56, 100);
    SDLSprite down_move(texture, 6, 10, 0, 0, 56, 100);

    AnimationPack animations(std::move(up_move), std::move(down_move),
                             std::move(left_move), std::move(right_move),
                             std::move(up_idle), std::move(down_idle),
                             std::move(left_idle), std::move(right_idle));

    return VisualComponent(std::move(animations), 5, 5, 1, 2);
}

void update_npc(VisualComponent &npc, SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                npc.set_orientation(RIGHT);
                npc.set_move_status(MOVING);
                npc.set_position(npc.get_x_tile() + 1,npc.get_y_tile());
                break;
            case SDLK_LEFT:
                npc.set_orientation(LEFT);
                npc.set_move_status(MOVING);
                npc.set_position(npc.get_x_tile() - 1,npc.get_y_tile());
                break;
            case SDLK_UP:
                npc.set_orientation(UP);
                npc.set_move_status(MOVING);
                npc.set_position(npc.get_x_tile(),npc.get_y_tile() - 1);
                break;
            case SDLK_DOWN:
                npc.set_orientation(DOWN);
                npc.set_move_status(MOVING);
                npc.set_position(npc.get_x_tile(),npc.get_y_tile() + 1);
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_UP:
            case SDLK_DOWN:
                npc.set_move_status(IDLE);
                break;
        }
    }
}
int main(void) {
    SDLWindow ventana(800, 600);
    SDLTextureLoader loader(ventana.init_renderer());

    SDLTexture sprite_texture =
        loader.load_texture("assets/sprite.png", 0, 0, 0);
    bool running = true;

    VisualComponent npc = load_component(sprite_texture);
    npc.set_move_status(IDLE);
    npc.set_orientation(DOWN);

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            update_npc(npc, e);
        }
        int xpos_pixels = npc.get_x_tile() * TILE_SIZE +
                          (npc.get_x_offset() * TILE_SIZE) / 100;
        int ypos_pixels = npc.get_y_tile() * TILE_SIZE +
                          (npc.get_y_offset() * TILE_SIZE) / 100;

        SDLArea dest(xpos_pixels, ypos_pixels, npc.get_width_tile() * TILE_SIZE,
                     npc.get_height_tile() * TILE_SIZE);

        ventana.fill(0, 143, 37, 255);
        npc.render(dest);

        ventana.render();
    }
    return 0;
}