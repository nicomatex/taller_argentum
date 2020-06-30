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
#include "inventory.h" 

int main(int argc, char const *argv[]) {
	ItemFactory item_factory("items.json");
	Inventory inventory;
	Gold* gold = static_cast<Gold*>(item_factory.create(500, 2000));
	std::cout << gold->get_data() << std::endl;
	Potion* potion = static_cast<Potion*>(item_factory.create(401, 1000));
	inventory.add(potion);
	Potion* potion2 = static_cast<Potion*>(item_factory.create(401, 3000));
	inventory.add(potion2);
	std::cout << inventory.get_data() << std::endl;
	std::cout << inventory.get_persist_data() << std::endl;
	Weapon* weapon = static_cast<Weapon*>(item_factory.create(300, 1));
	inventory.add(weapon);
	std::cout << inventory.remove(1)->get_data() << std::endl;
	std::cout << inventory.get_data() << std::endl;
	std::cout << inventory.get_persist_data() << std::endl;
	
	delete gold;
	delete potion;
	delete potion2;
	delete weapon;
	return 0;
}
