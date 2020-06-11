#include "resource_manager.h"

#include <fstream>
#include <iostream>

#include "engine_config.h"
#include "json.hpp"

using json = nlohmann::json;

void ResourceManager::_load_textures(SDLTextureLoader& loader,
                                     const std::string& texture_index_file) {
    std::cout << MSG_TEXTURES_LOADING << std::endl;

    std::ifstream input_file(texture_index_file);
    json texture_indexes = json::parse(input_file);

    for (auto texture_type = texture_indexes.begin();
         texture_type != texture_indexes.end(); ++texture_type) {
        std::string type(texture_type.key());
        std::string base_dir(texture_indexes[type]["basedir"]);

        for (auto& texture_info : texture_indexes[type]["textures"].items()) {
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

void ResourceManager::_load_animations(const std::string& sprite_index_file) {
    std::ifstream input_file(sprite_index_file);
    json sprite_info = json::parse(input_file);

    for (auto sprite_type_it = sprite_info["actors"].begin();
         sprite_type_it != sprite_info["actors"].end(); ++sprite_type_it) {
        std::string type(sprite_type_it.key());

        for (auto& animation_pack_info : sprite_info["actors"][type].items()) {
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

        for (auto& animation_info : sprite_info["decorations"][type].items()) {
            json info = animation_info.value();
            sprite_map[type].insert(std::make_pair(
                info["id"],
                SDLSprite(texture_map.at(type).at(info["texture"]), info)));
        }
    }
}

void ResourceManager::init(SDLTextureLoader& loader) {
    _load_textures(loader, TEXTURE_INDEX_FILE);
    _load_animations(SPRITE_INDEX_FILE);
}

ResourceManager& ResourceManager::get_instance() {
    static ResourceManager resource_manager;
    return resource_manager;
}

SDLTexture& ResourceManager::get_texture(const std::string& type, int id){
    return texture_map.at(type).at(id);
}


AnimationPack& ResourceManager::get_animation_pack(const std::string& type, int id){
    return animation_pack_map.at(type).at(id);
}

SDLSprite& ResourceManager::get_sprite(const std::string& type, int id){
    return sprite_map.at(type).at(id);
}

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}
