#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "actor.h"
#include "camera.h"
#include "decoration.h"
#include "include/SDL/sdl_texture_loader.h"
#include "include/SDL/sdl_window.h"
#include "include/json.hpp"
#include "visual_component.h"

typedef std::unordered_map<std::string,
                           std::unordered_map<std::string, SDLTexture>>
    TextureMap;

typedef std::unordered_map<std::string,
                           std::unordered_map<std::string, AnimationPack>>
    AnimationPackMap;

using json = nlohmann::json;

bool debug = true;

#define TILE_SIZE 64

#define BODY_WIDTH 25
#define BODY_HEIGHT 45

#define HEAD_WIDTH 17
#define HEAD_HEIGHT 17

/* Actor load_body(SDLTexture &texture_filename) {
    // return Actor(std::move(animations), 7, 7, 50, 100,0,0);
} */

/*Actor load_sprite(std::string type, std::string id, TextureMap &texture_map) {
    std::ifstream sprite_file("ind/sprites.json");
    json sprite_info = json::parse(sprite_file);
}*/

void load_textures(TextureMap &texture_map, SDLTextureLoader &loader) {
    std::cout << "Cargando texturas..." << std::endl;
    std::ifstream input_file("ind/textures.json");
    json texture_indexes = json::parse(input_file);

    for (auto texture_type = texture_indexes.begin();
         texture_type != texture_indexes.end(); ++texture_type) {
        std::string type(texture_type.key());
        std::string base_dir(texture_indexes[type]["basedir"]);

        for (auto texture_filename = texture_indexes[type]["textures"].begin();
             texture_filename != texture_indexes[type]["textures"].end();
             ++texture_filename) {
            std::string texture_address =
                base_dir + std::string(texture_filename.value());
            try {
                texture_map[type].insert(std::make_pair(
                    texture_filename.key(),
                    loader.load_texture(texture_address, 0, 0, 0)));

            } catch (std::exception) {
                std::cout << "Error cargando la textura " << texture_address
                          << std::endl;
            }
        }
    }
    std::cout << "Carga finalizada!" << std::endl;
}

void load_animation_packs(TextureMap &texture_map,
                          AnimationPackMap &animation_pack_map) {
    std::ifstream input_file("ind/sprites.json");
    json sprite_info = json::parse(input_file);

    for (auto sprite_type_it = sprite_info["actors"].begin();
         sprite_type_it != sprite_info["actors"].end(); ++sprite_type_it) {
        std::string type(sprite_type_it.key());

        for (auto animation_pack_info = sprite_info["actors"][type].begin();
             animation_pack_info != sprite_info["actors"][type].end();
             animation_pack_info++) {
            json pack_info = animation_pack_info.value();
            std::string pack_id(animation_pack_info.key());

            SDLSprite idle_down(texture_map.at(type).at(pack_info["texture"]),
                                pack_info["idle"]["down"]);
            SDLSprite idle_up(texture_map.at(type).at(pack_info["texture"]),
                              pack_info["idle"]["up"]);
            SDLSprite idle_left(texture_map.at(type).at(pack_info["texture"]),
                                pack_info["idle"]["left"]);
            SDLSprite idle_right(texture_map.at(type).at(pack_info["texture"]),
                                 pack_info["idle"]["right"]);
            SDLSprite moving_down(texture_map.at(type).at(pack_info["texture"]),
                                  pack_info["moving"]["down"]);
            SDLSprite moving_up(texture_map.at(type).at(pack_info["texture"]),
                                pack_info["moving"]["up"]);
            SDLSprite moving_left(texture_map.at(type).at(pack_info["texture"]),
                                  pack_info["moving"]["left"]);
            SDLSprite moving_right(
                texture_map.at(type).at(pack_info["texture"]),
                pack_info["moving"]["right"]);

            animation_pack_map[type].insert(std::make_pair(
                animation_pack_info.key(),
                AnimationPack(std::move(moving_up), std::move(moving_down),
                              std::move(moving_left), std::move(moving_right),
                              std::move(idle_up), std::move(idle_down),
                              std::move(idle_left), std::move(idle_right))));
        }
    }
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

    /*Actor npc = load_body(body_texture);
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
    int fps = 0;*/

    TextureMap texture_map;
    AnimationPackMap animation_pack_map;
    load_textures(texture_map, loader);
    load_animation_packs(texture_map, animation_pack_map);

    Actor head(animation_pack_map.at("bodies").at("1"),1,1,50,50,0,0);
    Camera camera(head);
    std::vector<VisualComponent *> components;
    components.push_back(&head);

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            update_npc(head, e);
        }

        ventana.fill(0, 51, 0, 255);
        camera.render_components(components);

        ventana.render();
        /*fps++;
        if (fps_timer.get_ticks() >= 1000) {
            std::cout << "[DEBUG] FPS: " << fps << std::endl;
            fps = 0;
            fps_timer.start();
        }
        std::cout << npc.get_x() << "-" << npc.get_y() << std::endl; */
    }
    return 0;
}
