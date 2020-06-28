#include "potion.h"

Potion::Potion() {}

Potion::Potion(item_info_t item_info, potion_info_t potion_info, uint32_t count) :
			   Item(item_info, count), potion_info(potion_info) {}

Potion::~Potion() {}

nlohmann::json Potion::get_info() {
	nlohmann::json info = Item::get_info();
	info["potion_info"] = potion_info;
	return std::move(info);
}