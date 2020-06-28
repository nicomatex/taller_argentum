#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include "json.h"
#include "item_factory.h"
#include "weapon.h"
#include "armor.h"
#include "gold.h"
#include "potion.h" 

int main(int argc, char const *argv[]) {
	ItemFactory item_factory("items.json");
	Weapon weapon = item_factory.create_weapon("Espada", 22);
	std::cout << weapon.get_info() << std::endl;

	Weapon weapon_espada = item_factory.create_weapon(300, 22);
	std::cout << weapon_espada.get_info() << std::endl;

	Armor armor = item_factory.create_armor("Escudo de tortuga", 3);
	std::cout << armor.get_info() << std::endl;
	Potion potion = item_factory.create_potion("Pocion de vida", 1000);
	std::cout << potion.get_info() << std::endl;
	Gold gold = item_factory.create_gold(9999);
	gold.decrease_stack(1000);
	
	std::cout << gold.get_info() << std::endl;
	return 0;
}
