#include "change_map_handler.h"

#include "../character_manager.h"
#include "../server_manager.h"
#include "event_factory.h"

// Temp
#include <iostream>

void ChangeMapHandler::handle(Event& event) {
    try {
        nlohmann::json json = event.get_json();
        ServerManager& server_manager = ServerManager::get_instance();
        nlohmann::json player_data = server_manager.change_player_map(
            json["client_id"], json["new_pos"], json["new_map_id"]);
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        character_manager.save();
        character_manager.set_character(player_data);
    } catch (const std::exception& e) {
        std::cerr << "ClientDropHandler: " << e.what() << std::endl;
    }
}

ChangeMapHandler::ChangeMapHandler() : BlockingThEventHandler() {
    std::cerr << "ChangeMapHandler: starting.." << std::endl;
}
