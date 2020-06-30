#include "client_initializer_handler.h"

#include "../game/map.h"
#include "../game/position.h"
#include "../server_manager.h"
#include "event_factory.h"

ClientInitializeHandler::ClientInitializeHandler(Event ev)
    : ThEventHandler(ev) {}

ClientInitializeHandler::~ClientInitializeHandler() {}

void ClientInitializeHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json connect_info = event.get_json();
    try {
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        std::string player_name = connect_info["player"]["name"];
        std::cout << "ClientInitializerHandler: Added player: " << player_name
                  << std::endl;
        nlohmann::json player_info =
            character_manager.get_character(player_name);
        server_manager.add_player(ClientId(connect_info["client_id"]),
                                  player_info);
    } catch (const CharacterNotFoundException& e) {
        // TODO: mejorar este handle
        server_manager.send_to(connect_info["client_id"],
                               EventFactory::disconnect());
        server_manager.rm_client(connect_info["client_id"]);
    }
}