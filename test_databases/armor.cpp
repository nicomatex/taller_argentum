#include "armor.h"

Armor::Armor() {}

Armor::Armor(item_info_t item_info, armor_info_t armor_info, uint32_t count) :
			 Item(item_info, count), armor_info(armor_info) {}

Armor::~Armor() {}

nlohmann::json Armor::get_info() {
	nlohmann::json info = Item::get_info();
	info["armor_info"] = armor_info;
	return std::move(info);
}