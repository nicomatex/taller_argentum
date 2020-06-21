#include <iostream>
#include "character_manager.h"

int main(int argc, char const *argv[]) {
	const char *file_characters = "characters.dat";
	const char *file_map_chars = "characters.json";
	CharacterManager char_manager(file_characters, file_map_chars);

	if (!char_manager.character_exists("nicolitox")) {
		character_t character_nico;
		character_nico = char_manager.create_character("nicolitox", 0, position_t{18,15}, 1, 2);
		char_manager.add_character(character_nico);	
	}
	
	if (!char_manager.character_exists("xxtaielxx")) {
		character_t character_taiel;
		character_taiel = char_manager.create_character("xxtaielxx", 0, position_t{20,21}, 2, 2);
		char_manager.add_character(character_taiel);
	}
	
	if (!char_manager.character_exists("fran")) {
		character_t character_fran;
		character_fran = char_manager.create_character("fran", 0, position_t{13,10}, 2, 1);
		char_manager.add_character(character_fran);
	}

	character_t char_result;
	try {
		char_result = char_manager.get_character("juan");
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	char_manager.print_character("nicolitox");
	char_manager.print_character("xxtaielxx");
	char_manager.print_character("fran");


	/*char_result = char_manager.get_character("nicolitox");
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
	std::cout << char_result2.body_id << std::endl;*/

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

/*
-------- PJ ID : 0 --------
Name: nicolitox
Map id: 0
X: 18 Y: 15
Head id: 1
Body id: 2


-------- PJ ID : 1 --------
Name: xxtaielxx
Map id: 0
X: 20 Y: 21
Head id: 2
Body id: 2


-------- PJ ID : 2 --------
Name: fran
Map id: 0
X: 13 Y: 10
Head id: 2
Body id: 1
*/