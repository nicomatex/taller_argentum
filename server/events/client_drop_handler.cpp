#include "client_drop_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/position.h"
#include "../map_monitor.h"
#include "../server_manager.h"

// Temp
#include <iostream>

void ClientDropHandler::handle(Event& event) {
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    CharacterManager& character_manager =
        server_manager.get_character_manager();
    nlohmann::json player_info = server_manager.rm_player(client_id);
    // Persistir datos
    character_manager.save();  // persisto el diccionario.
    character_manager.set_character(player_info);
    server_manager.rm_client(client_id);
}

ClientDropHandler::ClientDropHandler() : BlockingThEventHandler() {
    std::cerr << "ClientDropHandler: starting.." << std::endl;
}

ClientDropHandler::~ClientDropHandler() {}
