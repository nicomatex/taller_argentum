#include "armor.h"

Armor::Armor() {}

Armor::Armor(item_info_t item_info, armor_info_t armor_info, uint32_t stack)
    : Item(item_info, stack), armor_info(armor_info) {}

Armor::~Armor() {}

nlohmann::json Armor::get_data() {
    nlohmann::json info = Item::get_data();
    info["armor_info"] = armor_info;
    return info;
}