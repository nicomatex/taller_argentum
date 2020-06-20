#include <fstream>
#include <iostream>

#include "map.h"
#include "decoration.h"
#include "engine_config.h"
#include "json.hpp"
#include "resource_manager.h"
#include "engine_error.h"

using json = nlohmann::json;

void Map::generate(json map_description) {
    visual_layers.clear();
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
                    Decoration(tilesprite, j, i, 100, 100, 0, 0));
            }
        }
        visual_layers.push_back(std::move(new_layer));
    }
    is_valid = true;
}

Map::Map():is_valid(false){}

Map::Map(json map_description){
    generate(map_description);
}

std::vector<Decoration>& Map::get_layer(int n) { 
    if(!is_valid){
        throw EngineError(MSG_ERR_MAP_NOT_INITIALIZED);
    }
    return visual_layers[n]; 
}

int Map::get_width(){
    return width;
}

int Map::get_height(){
    return height;
}

Map::~Map() {}