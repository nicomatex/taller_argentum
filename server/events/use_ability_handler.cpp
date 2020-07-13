#include "use_ability_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_use_ability.h"
#include "../server_manager.h"

UseAbilityHandler::UseAbilityHandler() {}

void UseAbilityHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.push_action(client_id, new ActionUseAbility(json["target"]));
}
