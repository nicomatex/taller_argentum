#include "inventory_handler.h"

#include "../game/action_inventory.h"
#include "../map_monitor.h"
#include "../server_manager.h"

InventoryHandler::InventoryHandler() {}
InventoryHandler::~InventoryHandler() {}

void InventoryHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json_ev = event.get_json();
    ClientId client_id = json_ev["client_id"];
    uint8_t slot = json_ev["slot"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.push_action(client_id, new ActionInventory(slot));
}
