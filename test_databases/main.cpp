#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include "json.h"

typedef enum {weapon, armor, potion, gold} item_type_t;

typedef uint32_t ItemId;

typedef struct item_info {
	ItemId item_id;
	item_type_t item_type;
	int static_sprt_id;
	int dynamic_sprt_id;
} item_info_t;

inline void to_json(nlohmann::json& j, const item_info_t& i) {
	j["item_id"] = i.item_id;
    j["item_type"] = i.item_type;
    j["static_sprt_id"] = i.static_sprt_id;
    j["dynamic_sprt_id"] = i.dynamic_sprt_id;
}

inline void from_json(const nlohmann::json& j, item_info_t& i) {
	j["item_id"].get_to(i.item_id);
    j["item_type"].get_to(i.item_type);
	j["static_sprt_id"].get_to(i.static_sprt_id);
	j["dynamic_sprt_id"].get_to(i.dynamic_sprt_id);
}

typedef struct weapon_info {
	int min_damage;
	int max_damage;
} weapon_info_t;

inline void to_json(nlohmann::json& j, const weapon_info_t& w) {
	j["min_damage"] = w.min_damage;
    j["max_damage"] = w.max_damage;
}

inline void from_json(const nlohmann::json& j, weapon_info_t& w) {
	j["min_damage"].get_to(w.min_damage);
    j["max_damage"].get_to(w.max_damage);
}

typedef enum {helmet, chest, shield} slot_info_t;

typedef struct armor_info {
	int min_defense;
	int max_defense;
	slot_info_t slot_info;
} armor_info_t;

inline void to_json(nlohmann::json& j, const armor_info_t& a) {
	j["min_defense"] = a.min_defense;
    j["max_defense"] = a.max_defense;
}

inline void from_json(const nlohmann::json& j, armor_info_t& a) {
	j["min_defense"].get_to(a.min_defense);
    j["max_defense"].get_to(a.max_defense);
}

typedef struct potion_info {
	int health_increase;
	int mana_increase;
} potion_info_t;

inline void to_json(nlohmann::json& j, const potion_info_t& p) {
	j["health_increase"] = p.health_increase;
    j["mana_increase"] = p.mana_increase;
}

inline void from_json(const nlohmann::json& j, potion_info_t& p) {
	j["health_increase"].get_to(p.health_increase);
    j["mana_increase"].get_to(p.mana_increase);
}

int main(int argc, char const *argv[]) {
	/*
		Items json
		1-99 Cascos/Sombreros/etc
		100-199 Armaduras (chest)
		200-299 Escudos
		300-399 Armas
		400-499 Potions
		500 Misc
	*/
	std::ofstream o_items_stream("items.json");
	if (!o_items_stream.is_open()) throw std::exception();
	std::map<std::string, item_info_t> items_map;

	items_map["Capucha"] = item_info_t{1,armor,1,1};
	items_map["Casco de hierro"] = item_info_t{2,armor,2,2};
	items_map["Sombrero magico"] = item_info_t{3,armor,3,3};

	items_map["Armadura de cuero"] = item_info_t{100,armor,1,1};
	items_map["Armadura de placas"] = item_info_t{101,armor,2,2};
	items_map["Tunica azul"] = item_info_t{102,armor,3,3};

	items_map["Escudo de tortuga"] = item_info_t{200,armor,1,1};
	items_map["Escudo de hierro"] = item_info_t{201,armor,2,2};

	items_map["Espada"] = item_info_t{300,weapon,1,1};
	items_map["Arco simple"] = item_info_t{301,weapon,2,2};
	items_map["Arco compuesto"] = item_info_t{302,weapon,3,3};
	items_map["Vara de fresno"] = item_info_t{303,weapon,4,4};
	items_map["Baculo nudoso"] = item_info_t{304,weapon,5,5};
	items_map["Baculo engarzado"] = item_info_t{305,weapon,6,6};
	items_map["Flauta elfica"] = item_info_t{306,weapon,7,7};
	items_map["Hacha"] = item_info_t{307,weapon,8,8};
	items_map["Martillo"] = item_info_t{308,weapon,9,9};

	items_map["Pocion de vida"] = item_info_t{400,potion,1,0};
	items_map["Pocion de mana"] = item_info_t{401,potion,2,0};

	items_map["Oro"] = item_info_t{500,gold,1,0};

	nlohmann::json o_json_items = items_map;
	o_items_stream << o_json_items;
	o_items_stream.close();

	std::ifstream i_items_stream("items.json");
	if (!i_items_stream.is_open()) throw std::exception();
	nlohmann::json i_json_items;
	i_items_stream >> i_json_items;
	std::unordered_map<std::string, item_info_t> map_items = i_json_items;
	for (auto &value : map_items) {
		std::cout << "-------\n";
		std::cout << value.first << std::endl;
		std::cout << value.second.item_id << std::endl;
		std::cout << value.second.item_type << std::endl;
		std::cout << value.second.static_sprt_id << std::endl;
		std::cout << value.second.dynamic_sprt_id << std::endl;
	}

	/*
		Armors json (helmet, chest, shield)
	*/

	// Helmets

	std::ofstream o_helmets_stream("helmets.json");
	if (!o_helmets_stream.is_open()) throw std::exception();
	std::map<ItemId, armor_info_t> helmets_map;

	helmets_map[1]  = armor_info_t{1,4};  	// Capucha
	helmets_map[2] = armor_info_t{4,8}; 	// Casco de hierro
	helmets_map[3] = armor_info_t{4,12};	// Sombrero magico

	nlohmann::json o_json_helmets = helmets_map;
	o_helmets_stream << o_json_helmets;
	o_helmets_stream.close();

	// Armors

	std::ofstream o_armors_stream("armors.json");
	if (!o_armors_stream.is_open()) throw std::exception();
	std::map<ItemId, armor_info_t> armors_map;

	armors_map[100]  = armor_info_t{2,6};  // Armadura de cuero
	armors_map[101] = armor_info_t{15,30}; // Armadura de placas
	armors_map[102] = armor_info_t{6,10};  // Tunica azul

	nlohmann::json o_json_armors = armors_map;
	o_armors_stream << o_json_armors;
	o_armors_stream.close();

	// Shields

	std::ofstream o_shields_stream("shields.json");
	if (!o_shields_stream.is_open()) throw std::exception();
	std::map<ItemId, armor_info_t> shields_map;

	shields_map[200]  = armor_info_t{1,2};  // Escudo de tortuga
	shields_map[201] = armor_info_t{1,4}; 	// Escudo de hierro

	nlohmann::json o_json_shields = shields_map;
	o_shields_stream << o_json_shields;
	o_shields_stream.close();

	/*
		Weapons json
	*/

	std::ofstream o_weapons_stream("weapons.json");
	if (!o_weapons_stream.is_open()) throw std::exception();
	std::map<ItemId, weapon_info_t> weapons_map;

	weapons_map[300]  = weapon_info_t{2,5}; // Espada
	weapons_map[301] = weapon_info_t{1,4};	// Arco simple
	weapons_map[302] = weapon_info_t{4,16};	// Arco compuesto
	weapons_map[303] = weapon_info_t{0,0};	// Vara de fresno
	weapons_map[304] = weapon_info_t{0,0};	// Baculo nudoso
	weapons_map[305] = weapon_info_t{0,0};	// Baculo engarzado
	weapons_map[306] = weapon_info_t{0,0};	// Flauta elfica
	weapons_map[307] = weapon_info_t{4,5};	// Hacha
	weapons_map[308] = weapon_info_t{1,9};	// Martillo

	nlohmann::json o_json_weapons = weapons_map;
	o_weapons_stream << o_json_weapons;
	o_weapons_stream.close();

	/*
		Potions json
	*/

	std::ofstream o_potions_stream("potions.json");
	if (!o_potions_stream.is_open()) throw std::exception();
	std::map<ItemId, potion_info_t> potions_map;

	potions_map[400]  = potion_info_t{14,0};  	// Pocion de vida
	potions_map[401] = potion_info_t{0,30}; 	// Pocion de mana

	nlohmann::json o_json_potions = potions_map;
	o_potions_stream << o_json_potions;
	o_potions_stream.close();

	return 0;
}
