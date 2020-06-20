#include <iostream>
#include "character_manager.h"

int main(int argc, char const *argv[]) {
	const char *file_characters = "characters.dat";
	const char *file_map_chars = "characters.json";
	CharacterManager char_manager(file_characters, file_map_chars);
	
	character_t character = char_manager.create_character("nicolitox", 0, position_t{5,5}, 1, 1);
	char_manager.add_character(character);
	std::cout << char_manager.get_char_id("nicolitox") << std::endl;
	
	/*
	character_t character2 = char_manager.create_character("xxtaielxx", 22, position_t{3,4}, 2, 2);
	char_manager.add_character(character2);
	std::cout << char_manager.get_char_id("xxtaielxx") << std::endl;
	*/

	character_t char_result;
	try {
		char_result = char_manager.get_character("juan");
	} catch (...) {
		std::cerr << "Lanzo excepcion" << std::endl;
	}

	char_result = char_manager.get_character("nicolitox");
	std::cout << char_result.name << std::endl;
	std::cout << char_result.map_id << std::endl;
	std::cout << char_result.position.x << " " << char_result.position.y << std::endl;
	std::cout << char_result.head_id << std::endl;
	std::cout << char_result.body_id << std::endl;

	//
	char_result.map_id = 25;
	char_result.position = position_t{14,22};
	char_result.head_id = 0;
	char_result.body_id = 0;

	char_manager.set_character("nicolitox", char_result);
	character_t char_result2 = char_manager.get_character("nicolitox");
	std::cout << char_result2.name << std::endl;
	std::cout << char_result2.map_id << std::endl;
	std::cout << char_result2.position.x << " " << char_result.position.y << std::endl;
	std::cout << char_result2.head_id << std::endl;
	std::cout << char_result2.body_id << std::endl;

	/*
	char_result = char_manager.get_character("xxtaielxx");
	std::cout << char_result.name << std::endl;
	std::cout << char_result.map_id << std::endl;
	std::cout << char_result.position.x << " " << char_result.position.y << std::endl;
	std::cout << char_result.head_id << std::endl;
	std::cout << char_result.body_id << std::endl;
	*/
	//char_manager.save();
	return 0;
}
