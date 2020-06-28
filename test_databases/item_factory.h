#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include <map>
#include <unordered_map>
#include "armor.h"
#include "weapon.h"
#include "potion.h"
#include "gold.h"

class ItemNotFoundException : public std::exception {
   public:
    const char *what() const throw();
};

class ItemFactory {
   private:
	std::unordered_map<std::string, Armor> armors_map;
	std::unordered_map<std::string, Weapon> weapons_map;
	std::unordered_map<std::string, Potion> potions_map;
    Gold gold;
	bool item_exists(const std::string& name);
   public:
   	ItemFactory(const char *items_file);

   	Weapon create_weapon(const std::string& name, uint32_t count);
   	Armor create_armor(const std::string& name, uint32_t count);
   	Potion create_potion(const std::string& name, uint32_t count);

    Weapon create_weapon(ItemId item_id, uint32_t count);
    Armor create_armor(ItemId item_id, uint32_t count);
    Potion create_potion(ItemId item_id, uint32_t count);
    
   	Gold create_gold(uint32_t count);
    
   	~ItemFactory();
};

#endif // ITEM_FACTORY_H
