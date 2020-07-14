#include "inventory_handler.h"

#include "../game/actions/action_inventory.h"
#include "../server_manager.h"
#include "../session.h"

InventoryHandler::InventoryHandler() {}

void InventoryHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json_ev = event.get_json();
    ClientId client_id = json_ev["client_id"];
    uint8_t slot = json_ev["slot"];
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionInventory(slot));
}
