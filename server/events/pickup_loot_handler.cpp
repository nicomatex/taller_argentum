#include "pickup_loot_handler.h"

#include "../game/actions/action_loot.h"
#include "../map_monitor.h"
#include "../server_manager.h"

PickupLootHandler::PickupLootHandler() {}

void PickupLootHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json movement_info = event.get_json();
    ClientId client_id = movement_info["client_id"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.push_action(client_id, new ActionLoot());
}
