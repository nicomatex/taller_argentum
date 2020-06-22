#include "client_drop_handler.h"

#include "../nlohmann/json.hpp"
#include "map_monitor.h"
#include "server_manager.h"

ClientDropHandler::ClientDropHandler(Event ev) : ThEventHandler(ev) {}

void ClientDropHandler::run_handler() {
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json player_info = server_manager.rm_player(client_id);
    // TODO: Persistir datos
    server_manager.rm_client(client_id);
}

ClientDropHandler::~ClientDropHandler() {}
