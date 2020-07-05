#include "character_manager.h"

#include <iostream>

#include "../include/nlohmann/json.hpp"

const char* CharacterAlreadyExistsException::what() const throw() {
    return "Character already exists!";
}

const char* CharacterNotFoundException::what() const throw() {
    return "Character not found!";
}

CharacterManager::CharacterManager(const char* f_char, const char* f_map)
    : f_char_stream(f_char, std::fstream::binary | std::fstream::in |
                                std::fstream::out | std::fstream::ate),
      f_map_stream(f_map, std::fstream::in | std::fstream::out) {
    if (!f_char_stream.is_open()) {
        std::cerr << "Archivo de personajes inexistente" << std::endl;
        throw std::exception();
    }

    if (!f_map_stream.is_open()) {
        std::cerr << "Archivo de dict de personajes inexistente" << std::endl;
        throw std::exception();
    }

    nlohmann::json j_char_map;
    f_map_stream >> j_char_map;
    char_count = j_char_map["char_count"];
    char_map = j_char_map["char_map"].get<std::map<std::string, CharId>>();
}

CharacterManager::~CharacterManager() {
    save();
}

/**
 * @brief Devuelve un character por movimiento.
 *  Lanza std::exception() en caso de que name exceda MAX_LENGTH
 * 
 * @param character_info 
 * @return character_t 
 */
static character_t create_character(const nlohmann::json& character_info) {
    std::string name = character_info["name"];
    if (name.length() > MAX_CHAR_NAME)
        throw std::exception();
    character_t character;
    memset(&character, 0, sizeof(character_t));
    strncpy(character.name, name.data(), MAX_CHAR_NAME);
    character.map_id = character_info["map_id"];
    character.position = character_info["pos"];
    character.head_id = character_info["head_id"];
    character.body_id = character_info["body_id"];
    character.helmet_id = character_info["helmet_id"];
    character.armor_id = character_info["armor_id"];
    character.shield_id = character_info["shield_id"];
    character.weapon_id = character_info["weapon_id"];
    character.current_hp = character_info["curr_hp"];
    character.current_mp = character_info["curr_mp"];
    character.inventory = character_info["inventory"];
    character.class_type = character_info["class_type"];
    character.race_type = character_info["race_type"];
    character.current_level = character_info["curr_level"];
    character.current_exp = character_info["curr_exp"];
    return std::move(character);
}

void CharacterManager::add_character(const nlohmann::json& character_info) {
    std::unique_lock<std::mutex> l(m);
    character_t character = create_character(character_info);
    if (character_exists(character.name)) {
        throw CharacterAlreadyExistsException();
    }
    f_char_stream.seekg(0, std::ios_base::end);
    f_char_stream.write(reinterpret_cast<const char*>(&character),
                        sizeof(character_t));
    char_map[character.name] = char_count;
    char_count++;
}

bool CharacterManager::character_exists(std::string name) {
    return char_map.count(name);
}

void CharacterManager::set_character(const nlohmann::json& character_info) {
    std::unique_lock<std::mutex> l(m);
    CharId char_id = get_char_id(character_info["name"]);
    character_t character = create_character(character_info);
    f_char_stream.seekg(char_id * sizeof(character_t), std::ios_base::beg);
    f_char_stream.write(reinterpret_cast<const char*>(&character),
                        sizeof(character_t));
}

CharId CharacterManager::get_char_id(std::string name) {
    if (!character_exists(name))
        throw CharacterNotFoundException();
    return char_map.at(name);
}

nlohmann::json CharacterManager::get_character(std::string name) {
    std::unique_lock<std::mutex> l(m);
    CharId char_id = get_char_id(name);
    character_t character;
    f_char_stream.seekg(char_id * sizeof(character_t), std::ios_base::beg);
    f_char_stream.read(reinterpret_cast<char*>(&character),
                       sizeof(character_t));
    f_char_stream.clear();
    nlohmann::json character_info;
    character_info["name"] = std::string(character.name);
    character_info["map_id"] = character.map_id;
    character_info["pos"] = character.position;
    character_info["head_id"] = character.head_id;
    character_info["body_id"] = character.body_id;
    character_info["helmet_id"] = character.helmet_id;
    character_info["armor_id"] = character.armor_id;
    character_info["shield_id"] = character.shield_id;
    character_info["weapon_id"] = character.weapon_id;
    character_info["curr_hp"] = character.current_hp;
    character_info["curr_mp"] = character.current_mp;
    character_info["inventory"] = character.inventory;
    character_info["race_type"] = character.race_type;
    character_info["class_type"] = character.class_type;
    character_info["curr_level"] = character.current_level;
    character_info["curr_exp"] = character.current_exp;
    return std::move(character_info);
}

void CharacterManager::save() {
    std::unique_lock<std::mutex> l(m);
    f_map_stream.seekg(std::ios_base::beg);
    nlohmann::json j_char_map;
    j_char_map["char_count"] = char_count;
    j_char_map["char_map"] = char_map;
    f_map_stream << j_char_map;
}

void CharacterManager::print_character(std::string name) {
    nlohmann::json character = get_character(name);
    CharId char_id = get_char_id(name);
    std::cout << std::endl;
    std::cout << "-------- PJ ID : " << char_id << " --------" << std::endl;
    std::cout << "Name: " << character["name"] << std::endl;
    std::cout << "Map id: " << character["map_id"] << std::endl;
    std::cout << "X: " << character["pos"]["x"]
              << "Y: " << character["pos"]["y"] << std::endl;
    std::cout << "Head id: " << character["head_id"] << std::endl;
    std::cout << "Body id: " << character["body_id"] << std::endl;
    std::cout << "Helmet id: " << character["helmet_id"] << std::endl;
    std::cout << "Armor id: " << character["armor_id"] << std::endl;
    std::cout << "Shield id: " << character["shield_id"] << std::endl;
    std::cout << "Weapon id: " << character["weapon_id"] << std::endl;
    std::cout << "Current hp: " << character["curr_hp"] << std::endl;
    std::cout << "Current mp: " << character["curr_mp"] << std::endl;
    std::cout << "Inventory: " << character["inventory"] << std::endl;
    std::cout << "Class type: " << character["class_type"] << std::endl;
    std::cout << "Race type " << character["race_type"] << std::endl;
    std::cout << "Curr level: " << character["curr_level"] << std::endl;
    std::cout << "Curr exp " << character["curr_exp"] << std::endl;
    std::cout << std::endl;
}
