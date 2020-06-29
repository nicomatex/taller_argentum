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
    	id_to_str_map[item_info.id] = item_data["name"];
	}

	for (auto& it: json_items["weapons"].items() ) {
		nlohmann::json item_data = it.value();
		item_info_t item_info =  item_data["item_info"];
    	weapon_info_t weapon_info = item_data["weapon_info"];
    	weapons_map[item_data["name"]] = Weapon{item_info, weapon_info};
    	id_to_str_map[item_info.id] = item_data["name"];
	}

	for (auto& it: json_items["potions"].items()) {
		nlohmann::json item_data = it.value();
		item_info_t item_info =  item_data["item_info"];
    	potion_info_t potion_info = item_data["potion_info"];
    	potions_map[item_data["name"]] = Potion{item_info, potion_info};
    	id_to_str_map[item_info.id] = item_data["name"];
	}

	nlohmann::json item_data = json_items["miscellaneous"][0]; //Oro
	item_info_t item_info =  item_data["item_info"];
	gold = Gold{item_info};
	id_to_str_map[item_info.id] = item_data["name"];
}


Weapon* ItemFactory::create_weapon(const std::string& name, uint32_t stack) {
	if (!weapons_map.count(name)) throw ItemNotFoundException();
	Weapon* weapon = new Weapon(weapons_map.at(name));
	weapon->set_stack(stack);
	return weapon;
}

Armor* ItemFactory::create_armor(const std::string& name, uint32_t stack) {
	if (!armors_map.count(name)) throw ItemNotFoundException();
	Armor* armor = new Armor(armors_map.at(name));
	armor->set_stack(stack);
	return armor;
}

Potion* ItemFactory::create_potion(const std::string& name, uint32_t stack) {
	if (!potions_map.count(name)) throw ItemNotFoundException();
	Potion* potion = new Potion(potions_map.at(name));
	potion->set_stack(stack);
	return potion;
}

bool ItemFactory::item_exists(ItemId item_id) {
	return id_to_str_map.count(item_id);
}

Weapon* ItemFactory::create_weapon(ItemId item_id, uint32_t stack) {
	if (!item_exists(item_id)) throw ItemNotFoundException();
	return create_weapon(id_to_str_map.at(item_id), stack);
}

Armor* ItemFactory::create_armor(ItemId item_id, uint32_t stack) {
	if (!item_exists(item_id)) throw ItemNotFoundException();
	return create_armor(id_to_str_map.at(item_id), stack);
}

Potion* ItemFactory::create_potion(ItemId item_id, uint32_t stack){ 
	if (!item_exists(item_id)) throw ItemNotFoundException();
	return create_potion(id_to_str_map.at(item_id), stack);
}

Gold* ItemFactory::create_gold(uint32_t stack) {
	Gold* gold = new Gold(this->gold);
	gold->set_stack(stack);
	return gold;
}

ItemFactory::~ItemFactory() {}