#include "game_client.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include "actor.h"
#include "animation_pack.h"
#include "camera.h"
#include "client_config.h"
#include "include/SDL/sdl_animated_sprite.h"
#include "include/SDL/sdl_error.h"
#include "include/SDL/sdl_window.h"
#include "include/json.hpp"
#include "map.h"
#include "visual_component.h"

using json = nlohmann::json;

void GameClient::_load_textures(SDLTextureLoader &loader,
                                const std::string &texture_index_file) {
    std::cout << MSG_TEXTURES_LOADING << std::endl;

    std::ifstream input_file(texture_index_file);
    json texture_indexes = json::parse(input_file);

    for (auto texture_type = texture_indexes.begin();
         texture_type != texture_indexes.end(); ++texture_type) {
        std::string type(texture_type.key());
        std::string base_dir(texture_indexes[type]["basedir"]);

        for (auto &texture_info : texture_indexes[type]["textures"].items()) {
            json tex_info = texture_info.value();
            std::string texture_address =
                base_dir + std::string(tex_info["filename"]);
            try {
                if (tex_info["needs ckey"]) {
                    int ckey_r(tex_info["ckey"][0]);
                    int ckey_g(tex_info["ckey"][1]);
                    int ckey_b(tex_info["ckey"][2]);
                    texture_map[type].insert(std::make_pair(
                        tex_info["id"],
                        loader.load_texture(texture_address, ckey_r, ckey_g,
                                            ckey_b)));
                } else {
                    texture_map[type].insert(std::make_pair(
                        tex_info["id"], loader.load_texture(texture_address)));
                }

            } catch (std::exception) {
                std::cout << MSG_ERR_LOADING_TEXTURE << " " << texture_address
                          << std::endl;
            }
        }
    }
    std::cout << MSG_TEXTURES_FINISHED << std::endl;
}

void GameClient::_load_animations(const std::string &sprite_index_file) {
    std::ifstream input_file(sprite_index_file);
    json sprite_info = json::parse(input_file);

    for (auto sprite_type_it = sprite_info["actors"].begin();
         sprite_type_it != sprite_info["actors"].end(); ++sprite_type_it) {
        std::string type(sprite_type_it.key());

        for (auto &animation_pack_info : sprite_info["actors"][type].items()) {
            json pack_info = animation_pack_info.value();

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
                pack_info["id"],
                AnimationPack(std::move(moving_up), std::move(moving_down),
                              std::move(moving_left), std::move(moving_right),
                              std::move(idle_up), std::move(idle_down),
                              std::move(idle_left), std::move(idle_right))));
        }
    }

    for (auto sprite_type_it = sprite_info["decorations"].begin();
         sprite_type_it != sprite_info["decorations"].end(); ++sprite_type_it) {
        std::string type(sprite_type_it.key());

        for (auto &animation_info : sprite_info["decorations"][type].items()) {
            json info = animation_info.value();
            sprite_map[type].insert(std::make_pair(
                info["id"],
                SDLSprite(texture_map.at(type).at(info["texture"]), info)));
        }
    }
}

GameClient::GameClient(const std::string &texture_index_file,
                       const std::string &sprite_index_file)
    : main_window(960, 640, "Argentum Online") {
    try {
        SDLTextureLoader texture_loader(main_window.init_renderer());
        _load_textures(texture_loader, texture_index_file);
        _load_animations(sprite_index_file);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameClient::_update_game(SDL_Event &e) {}

void GameClient::_update_components(SDL_Event &e, Actor &player) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                player.move(RIGHT, 1);
                break;
            case SDLK_LEFT:
                player.move(LEFT, 1);
                break;
            case SDLK_UP:
                player.move(UP, 1);
                break;
            case SDLK_DOWN:
                player.move(DOWN, 1);
                break;
        }
    }
}

void GameClient::run() {
    bool running = true;
    Actor player(animation_pack_map.at("bodies").at(3), 10, 10, 50, 100, 20,
                 -20);
    Actor head(animation_pack_map.at("heads").at(3), 10, 10, 30, 30, 30, -100);
    Decoration portal(sprite_map.at("environment").at(1), 21, 5, 100, 200, 0,
                      0);

    std::vector<VisualComponent *> components;
    components.push_back(&player);
    components.push_back(&head);
    components.push_back(&portal);

    Camera camera(player, 50, 64);

    Map map("assets/maps/forest1.json", texture_map.at("tilesets").at(1));
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            _update_components(e, player);
            _update_components(e, head);
        }
        main_window.fill(0, 51, 0, 255);
        camera.render_map_layer(map.get_layer(0));
        camera.render_map_layer(map.get_layer(1));
        camera.render_components(components);

        main_window.render();
    }
}

GameClient::~GameClient() {}