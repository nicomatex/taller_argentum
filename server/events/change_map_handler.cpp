#include "change_map_handler.h"

#include "../character_manager.h"
#include "../server_manager.h"
#include "event_factory.h"

// Temp
#include <iostream>

void ChangeMapHandler::handle(Event& event) {
    nlohmann::json json = event.get_json();
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json player_data = server_manager.rm_player(json["client_id"]);
    player_data["map_id"] = json["new_map_id"];
    player_data["pos"] = json["new_pos"];
    server_manager.send_to(json["client_id"],
                           EventFactory::notify_map_change());
    CharacterManager& character_manager =
        server_manager.get_character_manager();
    character_manager.save();
    character_manager.set_character(player_data);
    server_manager.add_player(json["client_id"], player_data);
}

ChangeMapHandler::ChangeMapHandler() : BlockingThEventHandler() {
    std::cerr << "ChangeMapHandler: starting.." << std::endl;
}
