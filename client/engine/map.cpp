#include "map.h"

#include <fstream>
#include <iostream>

#include "../../include/nlohmann/json.hpp"
#include "decoration.h"
#include "engine_config.h"
#include "engine_error.h"
#include "resource_manager.h"
#include "visual_config.h"

using json = nlohmann::json;

void Map::generate(json map_description) {
    background_layers.clear();
    foreground_layers.clear();

    int tileset_id = map_description["properties"][TILESET_ID_INDEX]["value"];
    height = map_description["height"];
    width = map_description["width"];

    int tile_size = map_description["tilewidth"];
    int first_gid = 1;  // Cosas del tiled

    SDLTexture& tileset =
        ResourceManager::get_instance().get_texture("tilesets", tileset_id);

    int tiles_per_row = tileset.get_width() / tile_size;
    int rows = tileset.get_height() / tile_size;

    for (auto& layer : map_description["layers"].items()) {
        std::vector<Decoration> new_layer;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int tile_index = j + (i * width);
                int sprite_id =
                    int(layer.value()["data"][tile_index]) - first_gid;
                int sprite_base_x = (sprite_id % tiles_per_row) * tile_size;
                int sprite_base_y = (sprite_id / tiles_per_row) * tile_size;

                SDLSprite tilesprite(tileset, 1, 1, sprite_base_x,
                                     sprite_base_y, tile_size, tile_size);
                new_layer.push_back(
                    Decoration(tilesprite, j, i, FLOOR_TILE_CONFIG));
            }
        }
        bool over_player = false;
        for(auto &prop : layer.value()["properties"].items()){
            if(prop.value()["name"] == "over_player"){
                over_player = prop.value()["value"];
                break;
            }
        }
        if(over_player){
            foreground_layers.push_back(std::move(new_layer));
        }else{
            background_layers.push_back(std::move(new_layer));
        }
    }

    std::vector<Decoration> loot_layer;
    loot_layer_index = background_layers.size();
    background_layers.push_back(loot_layer);
    is_valid = true;
}

Map::Map() : is_valid(false) {}

Map::Map(json map_description) {
    generate(map_description);
}

int Map::get_width() {
    return width;
}

int Map::get_height() {
    return height;
}

std::vector<std::vector<Decoration>>& Map::get_background_layers(){
    if (!is_valid) {
        throw EngineError(MSG_ERR_MAP_NOT_INITIALIZED);
    }
    return background_layers;
}

std::vector<std::vector<Decoration>>& Map::get_foreground_layers(){
    if (!is_valid) {
        throw EngineError(MSG_ERR_MAP_NOT_INITIALIZED);
    }
    return foreground_layers;
}


Map::~Map() {}