#include "weapon.h"

Weapon::Weapon() {}

Weapon::Weapon(item_info_t item_info, weapon_info_t weapon_info, uint32_t count):
			   Item(item_info, count), weapon_info(weapon_info) {}

Weapon::~Weapon() {}

nlohmann::json Weapon::get_info() {
	nlohmann::json info = Item::get_info();
	info["weapon_info"] = weapon_info;
	return std::move(info);
}