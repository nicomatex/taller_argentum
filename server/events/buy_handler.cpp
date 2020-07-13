#include "buy_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_buy.h"
#include "../server_manager.h"

BuyHandler::BuyHandler() {}

void BuyHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    position_t target = json["target"];
    SlotId slot = json["slot"];
    uint32_t amount = json["amount"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.push_action(client_id, new ActionBuy(target, slot, amount));
}