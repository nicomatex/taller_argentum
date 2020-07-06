#include "loot_buffer.h"


LootBuffer::LootBuffer(){
    loot_info["items"] = nlohmann::json::array();
}

LootBuffer::~LootBuffer(){}

void LootBuffer::load_buffer(nlohmann::json new_loot_info){
    std::unique_lock<std::mutex> l(m);
    loot_info = new_loot_info;
}

void LootBuffer::flush(Map& map){
    std::unique_lock<std::mutex> l(m);
    map.update_loot_layer(loot_info);
}