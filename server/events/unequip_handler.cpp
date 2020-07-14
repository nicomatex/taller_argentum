#include "unequip_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_unequip.h"
#include "../server_manager.h"
#include "../session.h"

UnequipHandler::UnequipHandler() {}

void UnequipHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionUnequip(json["slot"]));
}
