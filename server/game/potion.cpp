#include "potion.h"

Potion::Potion() {}

Potion::Potion(item_info_t item_info, potion_info_t potion_info, uint32_t stack)
    : Item(item_info, stack), potion_info(potion_info) {}

Potion::~Potion() {}

nlohmann::json Potion::get_data() const {
    nlohmann::json info = Item::get_data();
    info["potion_info"] = potion_info;
    return std::move(info);
}