#include "resuscitate_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../game/actions/action_resuscitate.h"
#include "../server_manager.h"

ResuscitateHandler::ResuscitateHandler() {}

void ResuscitateHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json json = event.get_json();
    ClientId client_id = json["client_id"];
    position_t target = json["target"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.push_action(client_id, new ActionResucitate(target));
}
