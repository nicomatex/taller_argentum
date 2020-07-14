#include "character_manager.h"

#include <iostream>

#include "../include/my_exception.h"
#include "../include/nlohmann/json.hpp"

const char* CharacterNotFoundException::what() const throw() {
    return "Character not found!";
}

CharacterManager::CharacterManager(const char* f_char, const char* f_map)
    : f_char_stream(f_char, std::fstream::binary | std::fstream::in |
                                std::fstream::out | std::fstream::ate),
      f_map_stream(f_map, std::fstream::in | std::fstream::out) {
    if (!f_char_stream.is_open())
        throw MyException("CharacterManager: Error opening characters file: %s",
                          f_char);

    if (!f_map_stream.is_open())
        throw MyException(
            "CharacterManager: Error opening characters map file: %s", f_map);

    nlohmann::json j_char_map;
    f_map_stream >> j_char_map;
    char_count = j_char_map["char_count"];
    char_map = j_char_map["char_map"].get<std::map<std::string, CharId>>();

    if (!character_exists("nicomatex")) {
        nlohmann::json nico_info = {{"name", "nicomatex"},
                                    {"map_id", 0},
                                    {"pos", position_t{13, 21}},
                                    {"head_id", 1},
                                    {"body_id", 1},
                                    {"helmet_id", 1},
                                    {"armor_id", 100},
                                    {"shield_id", 200},
                                    {"weapon_id", 303},
                                    {"curr_hp", 57},
                                    {"curr_mp", 50},
                                    {"class_type", MAGE},
                                    {"race_type", HUMAN},
                                    {"curr_level", 13},
                                    {"curr_exp", 88000},
                                    {"alive", true}};

        nico_info["inventory"] =
            R"({"items_ids":[400,401,200,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[1372,521,1,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":1700})"_json;
        nico_info["vault"] =
            R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;
        add_character(nico_info);
    }

    if (!character_exists("tai")) {
        nlohmann::json taiel_info = {{"name", "tai"},
                                     {"map_id", 0},
                                     {"pos", position_t{20, 21}},
                                     {"head_id", 6},
                                     {"body_id", 2},
                                     {"helmet_id", 2},
                                     {"armor_id", 101},
                                     {"shield_id", 201},
                                     {"weapon_id", 302},
                                     {"curr_hp", 70},
                                     {"curr_mp", 0},
                                     {"class_type", WARRIOR},
                                     {"race_type", DWARF},
                                     {"curr_level", 14},
                                     {"curr_exp", 102000},
                                     {"alive", true}};
        taiel_info["inventory"] = R"({"items_ids":[400,401,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[3000,1500,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":2650})"_json;
        taiel_info["vault"] =
            R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;                                 
        add_character(taiel_info);
    }

    if (!character_exists("fran")) {
        nlohmann::json fran_info = {
            {"name", "fran"},   {"map_id", 0},      {"pos", position_t{13, 20}},
            {"head_id", 4},     {"body_id", 4},     {"helmet_id", 3},
            {"armor_id", 101},  {"shield_id", 201}, {"weapon_id", 301},
            {"curr_hp", 30},    {"curr_mp", 44},    {"class_type", PALADIN},
            {"race_type", ELF}, {"curr_level", 9},  {"curr_exp", 43000},
            {"alive", true}};
        fran_info["inventory"] =
            R"({"items_ids":[400,401,200,100,303,1,3,102,304,305,306,307],
                                 "items_stacks":[1200,500,3,2,2,1,1,1,1,1,1,1],
                                 "curr_gold":1681})"_json;
        fran_info["vault"] =
            R"({"items_ids":[400,401,200,100,303,1,3,102,304,305,306,307],
                                 "items_stacks":[1200,500,3,2,2,1,1,1,1,1,1,1],
                                 "curr_gold":30000})"_json;                                 
        add_character(fran_info);
    }

    if (!character_exists("eze")) {
        nlohmann::json eze_info = {{"name", "eze"},
                                   {"map_id", 0},
                                   {"pos", position_t{23, 20}},
                                   {"head_id", 10},
                                   {"body_id", 3},
                                   {"helmet_id", 1},
                                   {"armor_id", 101},
                                   {"shield_id", 200},
                                   {"weapon_id", 300},
                                   {"curr_hp", 60},
                                   {"curr_mp", 42},
                                   {"class_type", PRIEST},
                                   {"race_type", GNOME},
                                   {"curr_level", 24},
                                   {"curr_exp", 283000},
                                   {"alive", true}};
        eze_info["inventory"] =
            R"({"items_ids":[400,401,201,100,307,0,0,0,0,0,0,0],
                                 "items_stacks":[1200,780,1,2,2,0,0,0,0,0,0,0],
                                 "curr_gold":4800})"_json;
        eze_info["vault"] =
            R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;                                 
        add_character(eze_info);
    }
}

CharacterManager::~CharacterManager() {
    save();
}

/**
 * @brief Devuelve un character por movimiento.
 *        Lanza std::exception() en caso de que name exceda MAX_LENGTH
 *
 * @param character_info
 * @return character_t
 */
static character_t create_character(const nlohmann::json& character_info) {
    std::string name = character_info["name"];
    if (name.length() > MAX_CHAR_NAME)
        throw MyException("CharacterManager: Name: %s, exceeds max length : %d",
                          name, MAX_CHAR_NAME);
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
    character.alive = character_info["alive"];
    character.vault = character_info["vault"];
    return character;
}

void CharacterManager::add_character(const nlohmann::json& character_info) {
    std::unique_lock<std::mutex> l(m);
    character_t character = create_character(character_info);
    if (character_exists(character.name))
        throw MyException(
            "CharacterManager: Character with name: '%s' already exists",
            character.name);
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
    character_info["alive"] = character.alive;
    character_info["vault"] = character.vault;
    return character_info;
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
    std::cout << "Is alive " << character["alive"] << std::endl;
    std::cout << "Vault " << character["vault"] << std::endl;
    std::cout << std::endl;
}
