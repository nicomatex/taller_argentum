#include "map_decorations_buffer.h"
#include <iostream>

MapDecorationsBuffer::MapDecorationsBuffer(){
    loot_info["items"] = nlohmann::json::array();
}

MapDecorationsBuffer::~MapDecorationsBuffer(){}

void MapDecorationsBuffer::load_loot_info(nlohmann::json new_loot_info){
    std::unique_lock<std::mutex> l(m);
    loot_info = new_loot_info;
}

void MapDecorationsBuffer::flush_loot(Map& map){
    std::unique_lock<std::mutex> l(m);
    map.update_loot_layer(loot_info);
}

void MapDecorationsBuffer::push_special_ability(nlohmann::json ability_info){
    std::unique_lock<std::mutex> l(m);
    special_ability_queue.push(ability_info);
}


void MapDecorationsBuffer::flush_special_abilities(Map &map){
    std::unique_lock<std::mutex> l(m);
    while(!special_ability_queue.empty()){
        std::cout << "Pushing spell to map" << std::endl;
        map.push_spell(special_ability_queue.front());
        special_ability_queue.pop();
    }
}