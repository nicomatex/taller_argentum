#include "item_factory.h"

#include <fstream>
#include <iostream>

#include "../../../include/my_exception.h"
#include "special_attack.h"
#include "special_heal.h"

const char* ItemNotFoundException::what() const throw() {
    return "Item not found!";
}

SpecialAbility* ItemFactory::create_ability(const std::string& ability_name) {
    if (ability_name.length() == 0)
        return nullptr;
    SpecialAbility* ability = nullptr;
    const nlohmann::json& ability_data = abilities_map[ability_name];
    int ability_type = ability_data["ability_type"];
    switch (ability_type) {
        case 1:
            ability =
                new SpecialHeal(ability_data["ability_id"],
                                ability_data["heal"], ability_data["mp_cost"]);
            break;
        case 2:
            ability = new SpecialAttack(
                ability_data["ability_id"], ability_data["min_damage"],
                ability_data["max_damage"], ability_data["mp_cost"]);
            break;
        default:
            throw MyException(
                "ItemsFactory: create_ability: Tipo de habilidad desconocido: "
                "%i",
                ability_type);
            break;
    }
    return ability;
}

void ItemFactory::add_armors(const nlohmann::json& armors_data) {
    for (auto& it : armors_data.items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        armor_info_t armor_info = item_data["armor_info"];
        armors_map[item_info.id] = Armor{item_info, armor_info};
        id_to_type_map[item_info.id] = item_info.type;
    }
}

void ItemFactory::add_abilities(const nlohmann::json& abilities_data) {
    for (auto& it : abilities_data.items()) {
        abilities_map[it.key()] = it.value();
    }
}

void ItemFactory::add_weapons(const nlohmann::json& weapons_data) {
    for (auto& it : weapons_data.items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        weapon_info_t weapon_info = item_data["weapon_info"];
        weapons_map[item_info.id] = Weapon(item_info, weapon_info, nullptr);
        id_to_type_map[item_info.id] = item_info.type;
    }
}

void ItemFactory::add_potions(const nlohmann::json& potions_data) {
    for (auto& it : potions_data.items()) {
        nlohmann::json item_data = it.value();
        item_info_t item_info = item_data["item_info"];
        potion_info_t potion_info = item_data["potion_info"];
        potions_map[item_info.id] = Potion{item_info, potion_info};
        id_to_type_map[item_info.id] = item_info.type;
    }
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
        throw MyException("ItemFactory: Error opening items file: %s",
                          items_file);
    nlohmann::json json_items;
    istream >> json_items;

    add_armors(json_items["armors"]);

    add_abilities(json_items["abilities"]);

    add_weapons(json_items["weapons"]);

    add_potions(json_items["potions"]);

    item_info_t item_info = json_items["miscellaneous"]["Oro"];
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
            item = new Weapon(
                weapons_map.at(item_id),
                create_ability(weapons_map.at(item_id)
                                   .get_data()["weapon_info"]["ability"]));
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
