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
    std::unordered_map<ItemId, item_type_t> id_to_type_map;
	std::unordered_map<ItemId, Armor> armors_map;
	std::unordered_map<ItemId, Weapon> weapons_map;
	std::unordered_map<ItemId, Potion> potions_map;
    Gold _gold;
   public:
   	ItemFactory(const char *items_file);
    Item* create(ItemId item_id, uint32_t stack);
    bool item_exists(ItemId item_id);
   	~ItemFactory();
};

#endif // ITEM_FACTORY_H
