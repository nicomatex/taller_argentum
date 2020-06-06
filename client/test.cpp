#include <iostream>
#include <vector>

#include "actor.h"
#include "camera.h"
#include "decoration.h"
#include "include/SDL/sdl_texture_loader.h"
#include "include/SDL/sdl_window.h"
#include "visual_component.h"

bool debug = true;

#define TILE_SIZE 64

Actor load_component(SDLTexture &texture) {
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

    return Actor(std::move(animations), 5, 5, 1, 2);
}

void update_npc(Actor &npc, SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                npc.move(RIGHT, 1);
                break;
            case SDLK_LEFT:
                npc.move(LEFT, 1);
                break;
            case SDLK_UP:
                npc.move(UP, 1);
                break;
            case SDLK_DOWN:
                npc.move(DOWN, 1);
                break;
        }
    }
}

int main(void) {
    SDLWindow ventana(960, 640, "Argentum Online");
    SDLTextureLoader loader(ventana.init_renderer());

    SDLTexture sprite_texture =
        loader.load_texture("assets/sprite.png", 0, 0, 0);
    SDLTexture tree_texture =
        loader.load_texture("assets/arbolito.png", 0, 0, 0);
    SDLTexture portal_texture = loader.load_texture("assets/portal.png");
    SDLTexture explosion_texture = loader.load_texture("assets/explosion.png");
    SDLTexture floor_texture = loader.load_texture("assets/piso1.png");

    SDLSprite floor_sprite(floor_texture, 1, 1, 0, 0, 128, 128);
    SDLSprite portal_sprite(portal_texture, 4, 4, 0, 0, 250, 592);
    SDLSprite tree_sprite(tree_texture, 1, 1, 0, 0, 256, 256);
    SDLSprite explosion_sprite(explosion_texture, 25, 25, 0, 0, 130, 130);

    Decoration tree(tree_sprite, 5, 5, 5, 5);
    Decoration portal(portal_sprite, 10, 6, 1, 2);
    Decoration explosion(explosion_sprite, 10, 10, 2, 2);

    std::vector<VisualComponent *> floor_components;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            Decoration *floor = new Decoration(floor_sprite, i, j, 1, 1);
            floor_components.push_back(floor);
        }
    }

    Actor npc = load_component(sprite_texture);
    npc.set_position(0,0);
    Actor npc2 = load_component(sprite_texture);
    Camera camera(npc);
    std::vector<VisualComponent *> components;
    components.push_back(&portal);
    components.push_back(&tree);
    // components.push_back(&explosion);
    // components.push_back(&npc2);
    components.push_back(&npc);

    npc.set_move_status(IDLE);
    npc.set_orientation(DOWN);

    npc2.set_move_status(IDLE);
    npc2.set_orientation(UP);

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            update_npc(npc, e);
        }

        ventana.fill(0, 51, 0, 255);
        camera.render_components(floor_components);
        camera.render_components(components);
        ventana.render();
    }
    return 0;
}
