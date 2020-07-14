#include "sell_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_sell.h"
#include "../server_manager.h"
#include "../session.h"

SellHandler::SellHandler() {}

void SellHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    position_t target = json["target"];
    SlotId slot = json["slot"];
    uint32_t amount = json["amount"];
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionSell(target, slot, amount));
}
