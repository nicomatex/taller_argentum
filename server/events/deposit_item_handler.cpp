#include "deposit_item_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_deposit_item.h"
#include "../server_manager.h"
#include "../session.h"

DepositItemHandler::DepositItemHandler() {}

void DepositItemHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    position_t target = json["target"];
    SlotId slot = json["slot"];
    uint32_t amount = json["amount"];
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionDepositItem(target, slot, amount));
}
