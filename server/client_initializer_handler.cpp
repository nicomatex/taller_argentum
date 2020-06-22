#include "client_initializer_handler.h"

#include "map.h"
#include "position.h"
#include "server_manager.h"

ClientInitializeHandler::ClientInitializeHandler(Event ev)
    : ThEventHandler(ev) {}

ClientInitializeHandler::~ClientInitializeHandler() {}

void ClientInitializeHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    CharacterManager& char_manager = server_manager.get_character_manager();
    nlohmann::json connect_info = event.get_json();
    std::string player_name = connect_info["player"]["name"];
    std::cout << "Entered ClientInitializerHandler\n";
    character_t character = char_manager.get_character(player_name);
    nlohmann::json player_info = {{"name", character.name},
                                  {"map_id", character.map_id},
                                  {"pos", character.position},
                                  {"head_id", character.head_id},
                                  {"body_id", character.body_id}};
    server_manager.add_player(character.map_id, ClientId(connect_info["client_id"]),
                              player_info);
}