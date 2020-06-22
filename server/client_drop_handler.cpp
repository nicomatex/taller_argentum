#include "client_drop_handler.h"
#include "position.h"
#include "../nlohmann/json.hpp"
#include "map_monitor.h"
#include "server_manager.h"

ClientDropHandler::ClientDropHandler(Event ev) : ThEventHandler(ev) {}

void ClientDropHandler::run_handler() {
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    CharacterManager& char_manager = server_manager.get_character_manager();
    nlohmann::json player_info = server_manager.rm_player(client_id);
    //Persistir datos
    char_manager.save(); // persisto el diccionario.
    character_t character = char_manager.create_character(player_info["name"],
    													  player_info["map_id"],
    													  player_info["pos"],
    													  player_info["head_id"],
    													  player_info["body_id"]);
    char_manager.set_character(player_info["name"], character);
    server_manager.rm_client(client_id);
}

ClientDropHandler::~ClientDropHandler() {}
