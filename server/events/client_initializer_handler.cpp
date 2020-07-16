#include "client_initializer_handler.h"

#include "../game/position.h"
#include "../server_manager.h"
#include "event_factory.h"

void ClientInitializeHandler::handle(Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json connect_info = event.get_json();
    ClientId client_id = connect_info["client_id"];
    try {
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        std::string player_name = connect_info["player"]["name"];
        nlohmann::json player_info =
            character_manager.get_character(player_name);
        server_manager.add_name(client_id, player_name);
        server_manager.add_player(client_id, player_info);
        std::cout << "ClientInitializerHandler: Added player: " << player_name
                  << std::endl;
    } catch (const CharacterNotFoundException& e) {
        server_manager.send_to(client_id, EventFactory::name_not_found());
    } catch (const DuplicatedPlayerException& e) {
        server_manager.send_to(client_id, EventFactory::name_already_online());
    } catch (const std::exception& e) {
        std::cerr << "ClientInitializeHandler: " << e.what() << std::endl;
        return;
    }
}

ClientInitializeHandler::ClientInitializeHandler() : BlockingThEventHandler() {
    std::cerr << "ClientInitializeHandler: starting.." << std::endl;
}
