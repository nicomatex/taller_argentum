#include "drop_loot_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_drop.h"
#include "../server_manager.h"
#include "../session.h"

DropLootHandler::DropLootHandler() {}

void DropLootHandler::push_event(const Event& event) {
    nlohmann::json json = event.get_json();
    ServerManager& server_manager = ServerManager::get_instance();
    Session& session = server_manager.get_session(json["client_id"]);
    session.push_action(
        json["client_id"],
        new ActionDrop(json["slot"],
                       (json.contains("amount")) ? int(json["amount"]) : 1));
}
