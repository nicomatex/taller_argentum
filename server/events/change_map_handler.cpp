#include "change_map_handler.h"

#include "../server_manager.h"

// Temp
#include <iostream>

void ChangeMapHandler::handle(Event& event) {
    nlohmann::json json = event.get_json();
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.add_player(json["client_id"], json["player_info"]);
}

ChangeMapHandler::ChangeMapHandler() : BlockingThEventHandler() {
    std::cerr << "ChangeMapHandler: starting.." << std::endl;
}
ChangeMapHandler::~ChangeMapHandler() {}
