#include "map.h"
#include "include/json.hpp"
#include "decoration.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Map::Map(const std::string &map_file,SDLTexture &tileset){
    std::ifstream input_file(map_file);
    json map_info = json::parse(input_file);
    height = map_info["height"];
    width = map_info["width"];

    int tile_size = map_info["tilewidth"];
    int first_gid = 1;
    
    int tiles_per_row = tileset.get_width() / tile_size;
    int rows = tileset.get_height() / tile_size;

    for(auto &layer : map_info["layers"].items()){
        std::vector<Decoration> new_layer;
        for(int i = 0;i < height;i++){
            for(int j = 0; j < width;j++){
                int tile_index = j + (i * width);
                int sprite_id = int(layer.value()["data"][tile_index]) - first_gid;
                int sprite_base_x = (sprite_id % tiles_per_row) * tile_size;
                int sprite_base_y = (sprite_id / tiles_per_row) * tile_size;

                SDLSprite tilesprite(tileset,1,1,sprite_base_x,sprite_base_y,tile_size,tile_size);
                new_layer.push_back(Decoration(tilesprite,j,i,100,100,0,0));
            }
        }
        visual_layers.push_back(std::move(new_layer));
    }
}


std::vector<Decoration>& Map::get_layer(int n){
    return visual_layers[n];
}

Map::~Map(){}