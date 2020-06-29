#include "client_initializer_handler.h"

#include "../game/map.h"
#include "../game/position.h"
#include "../server_manager.h"

ClientInitializeHandler::ClientInitializeHandler(Event ev)
    : ThEventHandler(ev) {}

ClientInitializeHandler::~ClientInitializeHandler() {}

void ClientInitializeHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    CharacterManager& character_manager =
        server_manager.get_character_manager();
    nlohmann::json connect_info = event.get_json();
    std::string player_name = connect_info["player"]["name"];
    std::cout << "ClientInitializerHandler: Added player: " << player_name
              << std::endl;
    nlohmann::json player_info = character_manager.get_character(player_name);
    server_manager.add_player(ClientId(connect_info["client_id"]), player_info);
}