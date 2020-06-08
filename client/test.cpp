#include <iostream>
#include <vector>

#include "actor.h"
#include "camera.h"
#include "decoration.h"
#include "include/SDL/sdl_texture_loader.h"
#include "include/SDL/sdl_window.h"
#include "visual_component.h"

#include "include/json.hpp"
using json = nlohmann::json;

bool debug = true;

#define TILE_SIZE 64

#define BODY_WIDTH 25
#define BODY_HEIGHT 45

#define HEAD_WIDTH 17
#define HEAD_HEIGHT 17


Actor load_body(SDLTexture &texture) {
    SDLSprite right_idle(texture, 1, 1, 0, BODY_HEIGHT  * 3, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite left_idle(texture, 1, 1, 0, BODY_HEIGHT * 2, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite up_idle(texture, 1, 1, 0, BODY_HEIGHT, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite down_idle(texture, 1, 1, 0, 0, BODY_WIDTH, BODY_HEIGHT);

    SDLSprite right_move(texture, 5, 20, 0, BODY_HEIGHT  * 3, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite left_move(texture, 5, 20, 0, BODY_HEIGHT * 2, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite up_move(texture, 6, 20, 0, BODY_HEIGHT, BODY_WIDTH, BODY_HEIGHT);
    SDLSprite down_move(texture, 6, 20, 0, 0, BODY_WIDTH, BODY_HEIGHT);

    AnimationPack animations(std::move(up_move), std::move(down_move),
                             std::move(left_move), std::move(right_move),
                             std::move(up_idle), std::move(down_idle),
                             std::move(left_idle), std::move(right_idle));

    return Actor(std::move(animations), 7, 7, 50, 100,0,0);
}

Actor load_head(SDLTexture &texture) { 
    SDLSprite right_idle(texture, 1, 1, HEAD_WIDTH, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite left_idle(texture, 1, 1, HEAD_WIDTH * 2, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite up_idle(texture, 1, 1, HEAD_WIDTH * 3, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite down_idle(texture, 1, 1, 0, 0, HEAD_WIDTH, HEAD_HEIGHT);

    SDLSprite right_move(texture, 1, 1, HEAD_WIDTH, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite left_move(texture, 1, 1, HEAD_WIDTH * 2, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite up_move(texture, 1, 1, HEAD_WIDTH * 3, 0, HEAD_WIDTH, HEAD_HEIGHT);
    SDLSprite down_move(texture, 1, 1, 0, 0, HEAD_WIDTH, HEAD_HEIGHT);

    AnimationPack animations(std::move(up_move), std::move(down_move),
                             std::move(left_move), std::move(right_move),
                             std::move(up_idle), std::move(down_idle),
                             std::move(left_idle), std::move(right_idle));

    return Actor(std::move(animations), 7, 7, 40, 40,5,-80);     
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
        loader.load_texture("assets/sprites/npc/1.png", 0, 0, 0);
    SDLTexture body_texture = loader.load_texture("assets/sprites/character/bodies/1.png",0,0,0);
    SDLTexture head_texture = loader.load_texture("assets/sprites/character/heads/3.png",0,0,0);

    SDLTexture tree_texture =
        loader.load_texture("assets/sprites/environment/3.png", 0, 0, 0);
    SDLTexture portal_texture = loader.load_texture("assets/portal.png");
    SDLTexture floor_texture = loader.load_texture("assets/sprites/environment/2.png");

    SDLSprite floor_sprite(floor_texture, 1, 1, 0, 0, 128, 128);
    SDLSprite portal_sprite(portal_texture, 4, 4, 0, 0, 250, 592);
    SDLSprite tree_sprite(tree_texture, 1, 1, 0, 0, 256, 256);

    Decoration tree(tree_sprite, 5, 5, 500, 500,0,0);
    Decoration portal(portal_sprite, 10, 6, 100, 200,0,0);

    std::vector<VisualComponent *> floor_components;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            Decoration *floor = new Decoration(floor_sprite, i, j, 100, 100,0,0);
            floor_components.push_back(floor);
        }
    }

    Actor npc = load_body(body_texture);
    Actor head = load_head(head_texture);

    Camera camera(npc);
    std::vector<VisualComponent *> components;
    components.push_back(&portal);
    components.push_back(&npc);
    components.push_back(&head);
    components.push_back(&tree);
    npc.set_move_status(IDLE);
    npc.set_orientation(DOWN);
    bool running = true;
    
    SDLTimer fps_timer;
    fps_timer.start();
    int fps = 0;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            update_npc(npc, e);
            update_npc(head,e);
        }

        ventana.fill(0, 51, 0, 255);
        camera.render_components(floor_components);
        camera.render_components(components);

        ventana.render();
        fps++;
        if(fps_timer.get_ticks() >= 1000){
            std::cout << "[DEBUG] FPS: " << fps << std::endl;
            fps = 0;
            fps_timer.start();
        }
        std::cout << npc.get_x() << "-" << npc.get_y() << std::endl;
    }
    return 0;
}
