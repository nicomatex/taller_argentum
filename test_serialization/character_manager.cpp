#include "character_manager.h"
#include <iostream>
#include "json.h"

const char* CharacterAlreadyExistsException::what() const throw(){
    return "Character already exists!";
}

const char* CharacterNotFoundException::what() const throw(){
    return "Character not found!";
}

CharacterManager::CharacterManager(const char *f_char,
	                               const char *f_map) :
                                   f_char_stream(f_char, std::fstream::binary |
                                   std::fstream::in | std::fstream::out |
                                   std::fstream::ate),
                                   f_map_stream(f_map, std::fstream::in |
                                   std::fstream::out) {

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

character_t CharacterManager::create_character(std::string name, int map_id,
											   position_t pos_character,
											   int head_id, int body_id) {
    if (name.length() > MAX_CHAR_NAME) throw std::exception();
	character_t character;
	memset(&character, 0 ,sizeof(character_t));
	strncpy(character.name, name.data(), MAX_CHAR_NAME);
	character.map_id = map_id;
	character.position = pos_character;
	character.head_id = head_id;
	character.body_id = body_id;
    return std::move(character);
}

void CharacterManager::add_character(const character_t &character) {
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

void CharacterManager::set_character(std::string name,
								     const character_t &character) {
    CharId char_id = get_char_id(name);
    if (char_id != get_char_id(character.name)) throw std::exception();
    f_char_stream.seekg(char_id * sizeof(character_t), std::ios_base::beg);
    f_char_stream.write(reinterpret_cast<const char*>(&character),
                        sizeof(character_t));
}


CharId CharacterManager::get_char_id(std::string name) {
    if (!character_exists(name)) throw CharacterNotFoundException();
    return char_map.at(name);
}

character_t CharacterManager::get_character(std::string name) {
    CharId char_id = get_char_id(name);
    character_t character;
    f_char_stream.seekg(char_id * sizeof(character_t), std::ios_base::beg);
    f_char_stream.read(reinterpret_cast<char*>(&character),sizeof(character_t));
    f_char_stream.clear();
    return std::move(character);
}

void CharacterManager::save() {
    f_map_stream.seekg(std::ios_base::beg);
    nlohmann::json j_char_map;
    j_char_map["char_count"] = char_count;
    j_char_map["char_map"] = char_map;
    f_map_stream << j_char_map;
}

void CharacterManager::print_character(std::string name) {
    character_t character = get_character(name);
    CharId char_id = get_char_id(name);
    std::cout << std::endl;
    std::cout << "-------- PJ ID : " << char_id << " --------" << std::endl;
    std::cout << "Name: " << character.name << std::endl;
    std::cout << "Map id: " << character.map_id << std::endl;
    std::cout << "X: " << character.position.x <<
                " Y: " << character.position.y << std::endl;                  
    std::cout << "Head id: " << character.head_id << std::endl;
    std::cout << "Body id: " << character.body_id << std::endl;
    std::cout << std::endl;
}
