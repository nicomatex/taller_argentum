#include "item_factory.h"

#include <exception>
#include <fstream>
#include <iostream>

const char* ItemNotFoundException::what() const throw() {
    return "Item not found!";
}

ItemFactory::ItemFactory(const char* items_file) {
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
    if (!istream.is_open())
        throw std::exception();
    nlohmann::json json_items;
    istream >> json_items;

    for (auto& it : json_items["armors"].items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        armor_info_t armor_info = item_data["armor_info"];
        armors_map[item_info.id] = Armor{item_info, armor_info};
        id_to_type_map[item_info.id] = item_info.type;
    }

    for (auto& it : json_items["weapons"].items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        weapon_info_t weapon_info = item_data["weapon_info"];
        weapons_map[item_info.id] = Weapon{item_info, weapon_info};
        id_to_type_map[item_info.id] = item_info.type;
    }

    for (auto& it : json_items["potions"].items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        potion_info_t potion_info = item_data["potion_info"];
        potions_map[item_info.id] = Potion{item_info, potion_info};
        id_to_type_map[item_info.id] = item_info.type;
    }

    nlohmann::json item_data = json_items["miscellaneous"][0];  // Oro
    item_info_t item_info = item_data["item_info"];
    _gold = Gold{item_info};
    id_to_type_map[item_info.id] = item_info.type;
}

bool ItemFactory::item_exists(ItemId item_id) {
    return id_to_type_map.count(item_id);
}

Item* ItemFactory::create(ItemId item_id, uint32_t stack) {
    if (!item_exists(item_id))
        throw ItemNotFoundException();
    item_type_t item_type = id_to_type_map.at(item_id);
    Item* item = nullptr;
    switch (item_type) {
        case TYPE_WEAPON:
            item = new Weapon(weapons_map.at(item_id));
            break;
        case TYPE_ARMOR:
            item = new Armor(armors_map.at(item_id));
            break;
        case TYPE_POTION:
            item = new Potion(potions_map.at(item_id));
            break;
        case TYPE_GOLD:
            item = new Gold(_gold);
            break;
        default:
            std::cerr << "Error al crear" << std::endl;
            break;
    }
    item->set_stack(stack);
    return item;
}

ItemFactory::~ItemFactory() {}