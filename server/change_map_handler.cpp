#include "change_map_handler.h"

#include "server_manager.h"

// Temp
#include <iostream>

void ChangeMapHandler::run_handler() {
    nlohmann::json json = event.get_json();
    std::cerr << json << std::endl;
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.add_player(json["client_id"], json["player_info"]);
}

ChangeMapHandler::ChangeMapHandler(Event ev) : ThEventHandler(ev) {}
ChangeMapHandler::~ChangeMapHandler() {}
