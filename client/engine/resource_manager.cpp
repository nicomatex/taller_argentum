#include "resource_manager.h"

#include <fstream>
#include <iostream>

#include "../../include/nlohmann/json.hpp"
#include "asset_loading_error.h"
#include "engine_config.h"

using json = nlohmann::json;

ResourceManager::ResourceManager() {}

void ResourceManager::_load_textures(SDLTextureLoader& loader,
                                     const std::string& texture_index_file) {
    std::cout << MSG_TEXTURES_LOADING << std::endl;

    try {
        std::ifstream input_file(texture_index_file);
        json texture_indexes = json::parse(input_file);
        for (auto texture_type = texture_indexes.begin();
             texture_type != texture_indexes.end(); ++texture_type) {
            std::string type(texture_type.key());
            std::string base_dir(texture_indexes[type]["basedir"]);

            for (auto& texture_info :
                 texture_indexes[type]["textures"].items()) {
                json tex_info = texture_info.value();
                std::string texture_address =
                    base_dir + std::string(tex_info["filename"]);

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
            }
        }
    } catch (std::exception& e) {
        throw AssetLoadingError("Error loading textures.");
    }
    std::cout << MSG_TEXTURES_FINISHED << std::endl;
}

void ResourceManager::_load_animations(const std::string& sprite_index_file) {
    try {
        std::ifstream input_file(sprite_index_file);
        json sprite_info = json::parse(input_file);
        for (auto sprite_type_it = sprite_info["actors"].begin();
             sprite_type_it != sprite_info["actors"].end(); ++sprite_type_it) {
            std::string type(sprite_type_it.key());

            for (auto& animation_pack_info :
                 sprite_info["actors"][type].items()) {
                json pack_info = animation_pack_info.value();

                SDLSprite idle_down(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["idle"]["down"]);
                SDLSprite idle_up(texture_map.at(type).at(pack_info["texture"]),
                                  pack_info["idle"]["up"]);
                SDLSprite idle_left(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["idle"]["left"]);
                SDLSprite idle_right(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["idle"]["right"]);
                SDLSprite moving_down(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["moving"]["down"]);
                SDLSprite moving_up(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["moving"]["up"]);
                SDLSprite moving_left(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["moving"]["left"]);
                SDLSprite moving_right(
                    texture_map.at(type).at(pack_info["texture"]),
                    pack_info["moving"]["right"]);

                animation_pack_map[type].insert(std::make_pair(
                    pack_info["id"],
                    AnimationPack(moving_up, moving_down, moving_left,
                                  moving_right, idle_up, idle_down, idle_left,
                                  idle_right)));
            }
        }

        for (auto sprite_type_it = sprite_info["decorations"].begin();
             sprite_type_it != sprite_info["decorations"].end();
             ++sprite_type_it) {
            std::string type(sprite_type_it.key());

            for (auto& animation_info :
                 sprite_info["decorations"][type].items()) {
                json info = animation_info.value();
                sprite_map[type].insert(std::make_pair(
                    info["id"],
                    SDLSprite(texture_map.at(type).at(info["texture"]), info)));
            }
        }
    } catch (std::exception& e) {
        throw AssetLoadingError("Error generando sprites");
    }
}

void ResourceManager::_load_fonts(const std::string& font_index_file) {
    try {
        std::ifstream input_file(font_index_file);
        json fonts_info = json::parse(input_file);
        std::string basedir = fonts_info["truetype"]["basedir"];
        for (auto& font : fonts_info["truetype"]["fonts"].items()) {
            json font_info = font.value();
            std::string filename = font_info["filename"];
            std::string font_address = basedir + filename;
            int font_id = font_info["id"];
            TTF_Font* ttf_font = TTF_OpenFont(font_address.c_str(), 28);
            font_map.insert(std::make_pair(font_id, ttf_font));
        }

        for (auto& font : fonts_info["bitmap"]["fonts"].items()) {
            json font_info = font.value();
            int font_id = font_info["id"];
            SDLBitmapFont bitmap_font(
                get_texture("bitmap_fonts", font_info["texture_id"]),
                font_info["first_ascii_char"], font_info["char_width"],
                font_info["char_height"], font_info["chars_per_row"]);
            bitmap_font_map.insert(std::make_pair(font_id, bitmap_font));
        }
    } catch (std::exception& e) {
        throw AssetLoadingError("Error loading fonts.");
    }
}

void ResourceManager::_load_audio(const std::string& audio_index_file) {
    try {
        std::ifstream input_file(audio_index_file);
        json audio_info = json::parse(input_file);
        std::string music_basedir = audio_info["music"]["basedir"];
        for (auto& it : audio_info["music"]["files"].items()) {
            json music_file_info = it.value();
            int id = music_file_info["id"];
            std::string file_address =
                music_basedir + std::string(music_file_info["filename"]);
            music_map.emplace(id, file_address);
        }

        std::string sfx_basedir = audio_info["sfx"]["basedir"];
        for (auto& it : audio_info["sfx"]["files"].items()) {
            json sfx_file_info = it.value();
            int id = sfx_file_info["id"];
            std::string file_address =
                sfx_basedir + std::string(sfx_file_info["filename"]);
            sound_fx_map.emplace(id, file_address);
        }

    } catch (std::exception& e) {
        throw AssetLoadingError("Error loading audio files.");
    }
}

void ResourceManager::init(SDLTextureLoader& loader) {
    _load_textures(loader, TEXTURE_INDEX_FILE);
    _load_animations(SPRITE_INDEX_FILE);
    _load_fonts(FONT_INDEX_FILE);
    _load_audio(AUDIO_INDEX_FILE);
}

ResourceManager& ResourceManager::get_instance() {
    static ResourceManager resource_manager;
    return resource_manager;
}

SDLTexture& ResourceManager::get_texture(const std::string& type, int id) {
    if (texture_map.count(type) == 0) {
        throw AssetLoadingError("No such texture type: %s", type);
    }

    if (texture_map.at(type).count(id) == 0) {
        throw AssetLoadingError("No such texture id: %d, within type %s", id,
                                type);
    }
    return texture_map.at(type).at(id);
}

AnimationPack& ResourceManager::get_animation_pack(const std::string& type,
                                                   int id) {
    if (animation_pack_map.count(type) == 0) {
        throw AssetLoadingError("No such AnimationPack type: %s", type);
    }

    if (texture_map.at(type).count(id) == 0) {
        throw AssetLoadingError("No such AnimationPack id: %d, within type %s",
                                id, type);
    }
    return animation_pack_map.at(type).at(id);
}

SDLSprite& ResourceManager::get_sprite(const std::string& type, int id) {
    if (sprite_map.count(type) == 0) {
        throw AssetLoadingError("No such Sprite type: %s", type);
    }

    if (sprite_map.at(type).count(id) == 0) {
        throw AssetLoadingError("No such Sprite id: %d, within type %s", id,
                                type);
    }
    return sprite_map.at(type).at(id);
}

TTF_Font* ResourceManager::get_font(int id) {
    if (font_map.count(id) == 0) {
        throw AssetLoadingError("No such font id: %d");
    }
    return font_map.at(id);
}

SDLBitmapFont& ResourceManager::get_bitmap_font(int id){
    if (bitmap_font_map.count(id) == 0) {
        throw AssetLoadingError("No such font id: %d");
    }
    return bitmap_font_map.at(id);
}

void ResourceManager::free_resources() {
    for (auto& it : font_map) {
        TTF_CloseFont(it.second);
    }
}

SDLMusic& ResourceManager::get_music(int id) {
    if (music_map.count(id) == 0) {
        throw AssetLoadingError("No such music id: %d", id);
    }
    return music_map.at(id);
}

SDLSoundFx& ResourceManager::get_sound_fx(int id) {
    if (sound_fx_map.count(id) == 0) {
        throw AssetLoadingError("No such sound fx id: %d", id);
    }
    return sound_fx_map.at(id);
}

ResourceManager::~ResourceManager() {}
