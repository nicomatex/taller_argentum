#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include <map>
#include <unordered_map>

#include "armor.h"
#include "gold.h"
#include "potion.h"
#include "special_ability.h"
#include "weapon.h"

class ItemNotFoundException : public std::exception {
   public:
    const char* what() const throw();
};

class ItemFactory {
   private:
    std::unordered_map<ItemId, item_type_t> id_to_type_map;
    std::unordered_map<ItemId, Armor> armors_map;
    std::unordered_map<std::string, nlohmann::json> abilities_map;
    std::unordered_map<ItemId, Weapon> weapons_map;
    std::unordered_map<ItemId, Potion> potions_map;
    Gold _gold;

    void add_armors(const nlohmann::json& armors_data);

    void add_abilities(const nlohmann::json& abilities_data);

    void add_weapons(const nlohmann::json& weapons_data);

    void add_potions(const nlohmann::json& potions_data);

    SpecialAbility* create_ability(const std::string& ability_name);

   public:
    ItemFactory(const char* items_file);
    /**
     * @brief Devuelve una copia del item en memoria, con su respectiva cantidad.
     *  En caso de no existir el item_id, lanza ItemNotFoundException.
     * 
     * @param item_id 
     * @param stack 
     * @return Item* 
     */
    Item* create(ItemId item_id, uint32_t stack);
    bool item_exists(ItemId item_id);
    ~ItemFactory();
};

#endif  // ITEM_FACTORY_H
