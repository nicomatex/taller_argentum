#include "weapon.h"

#include "random_event_generator.h"

Weapon::Weapon() {}

Weapon::Weapon(item_info_t item_info, weapon_info_t weapon_info, uint32_t stack)
    : Item(item_info, stack), weapon_info(weapon_info) {}

Weapon::~Weapon() {}

int Weapon::deal_damage() {
    return (int)RandomEventGenerator::random_in(weapon_info.min_damage,
                                                weapon_info.max_damage);
}

nlohmann::json Weapon::get_data() {
    nlohmann::json info = Item::get_data();
    info["weapon_info"] = weapon_info;
    return std::move(info);
}