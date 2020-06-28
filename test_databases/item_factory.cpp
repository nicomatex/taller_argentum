#include "item_factory.h"
#include <iostream>
#include <fstream>
#include <exception>

const char* ItemNotFoundException::what() const throw() {
    return "Item not found!";
}

ItemFactory::ItemFactory(const char *items_file) {
	/*
		Items json
		1-99 Cascos/Sombreros/etc
		100-199 Armaduras (chest)
		200-299 Escudos
		300-399 Armas
		400-499 Potions
		500 Misc -> Oro
	*/
	std::ifstream istream(items_file);
	if (!istream.is_open()) throw std::exception();
	nlohmann::json json_items;
	istream >> json_items;

	
	for (auto& it: json_items["armors"].items()) {
		nlohmann::json item_data = it.value();
		item_info_t item_info =  item_data["item_info"];
    	armor_info_t armor_info = item_data["armor_info"];
    	armors_map[item_data["name"]] = Armor{item_info, armor_info};
	}

	for (auto& it: json_items["weapons"].items() ) {
		nlohmann::json item_data = it.value();
		item_info_t item_info =  item_data["item_info"];
    	weapon_info_t weapon_info = item_data["weapon_info"];
    	weapons_map[item_data["name"]] = Weapon{item_info, weapon_info};
	}

	for (auto& it: json_items["potions"].items()) {
		nlohmann::json item_data = it.value();
		item_info_t item_info =  item_data["item_info"];
    	potion_info_t potion_info = item_data["potion_info"];
    	potions_map[item_data["name"]] = Potion{item_info, potion_info};
	}


	gold = Gold{json_items["miscellaneous"][0]["item_info"]};
}


Weapon ItemFactory::create_weapon(const std::string& name, uint32_t count) {
	if (!weapons_map.count(name)) throw ItemNotFoundException();
	Weapon weapon(weapons_map.at(name));
	weapon.set_count(count);
	return std::move(weapon);
}

Armor ItemFactory::create_armor(const std::string& name, uint32_t count) {
	if (!armors_map.count(name)) throw ItemNotFoundException();
	Armor armor(armors_map.at(name));
	armor.set_count(count);
	return std::move(armor);
}

Potion ItemFactory::create_potion(const std::string& name, uint32_t count) {
	if (!potions_map.count(name)) throw ItemNotFoundException();
	Potion potion(potions_map.at(name));
	potion.set_count(count);
	return std::move(potion);
}

Gold ItemFactory::create_gold(uint32_t count) {
	Gold gold = this->gold;
	gold.set_count(count);
	return std::move(gold);
}


ItemFactory::~ItemFactory() {}