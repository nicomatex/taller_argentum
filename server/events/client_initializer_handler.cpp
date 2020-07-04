#include "client_initializer_handler.h"

#include "../game/map.h"
#include "../game/position.h"
#include "../server_manager.h"
#include "event_factory.h"

void ClientInitializeHandler::handle(Event& event) {
    try {
        ServerManager& server_manager = ServerManager::get_instance();
        nlohmann::json connect_info = event.get_json();
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        std::string player_name = connect_info["player"]["name"];
        server_manager.add_name(connect_info["client_id"], player_name);
        std::cout << "ClientInitializerHandler: Adding player: " << player_name
                  << std::endl;
        nlohmann::json player_info =
            character_manager.get_character(player_name);
        server_manager.add_player(connect_info["client_id"], player_info);
    } catch (const CharacterNotFoundException& e) {
        disconnect(event);
    } catch (const DuplicatedPlayerException& e) {
        disconnect(event);
    } catch (const std::exception& e) {
        std::cerr << "initialize_handler: " << e.what() << std::endl;
        return;
    }
}

void ClientInitializeHandler::disconnect(Event& event) const {
    // TODO: mejorar este handle
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json connect_info = event.get_json();
    server_manager.send_to(connect_info["client_id"],
                           EventFactory::disconnect());
    std::cout << "Sending drop to " << connect_info["client_id"] << std::endl;
    server_manager.rm_client(connect_info["client_id"]);
}

ClientInitializeHandler::ClientInitializeHandler() : BlockingThEventHandler() {
    std::cerr << "ClientInitializeHandler: starting.." << std::endl;
}

ClientInitializeHandler::~ClientInitializeHandler() {}
