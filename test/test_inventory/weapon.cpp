#include "weapon.h"

Weapon::Weapon() {}

Weapon::Weapon(item_info_t item_info, weapon_info_t weapon_info, uint32_t stack)
    : Item(item_info, stack), weapon_info(weapon_info) {}

Weapon::~Weapon() {}

nlohmann::json Weapon::get_data() {
    nlohmann::json info = Item::get_data();
    info["weapon_info"] = weapon_info;
    return info;
}