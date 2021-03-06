#include "client_drop_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../character_manager.h"
#include "../server_manager.h"

// Temp
#include <iostream>

void ClientDropHandler::handle(Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    try {
        ClientId client_id = event.get_json()["client_id"];
        nlohmann::json player_info = server_manager.rm_player(client_id);
        // Persistir datos
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        character_manager.save();  // persisto el diccionario.
        character_manager.set_character(player_info);
        server_manager.rm_client(client_id);
    } catch (const ClientDisconnectedException& e) {
        ClientId client_id = event.get_json()["client_id"];
        server_manager.rm_client(client_id);
        std::cerr << "Catched disconnect\n";
    } catch (const std::exception& e) {
        std::cerr << "ClientDropHandler: " << e.what() << std::endl;
    }
}

ClientDropHandler::ClientDropHandler() : BlockingThEventHandler() {
    std::cerr << "ClientDropHandler: starting.." << std::endl;
}
