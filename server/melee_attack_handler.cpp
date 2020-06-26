#include "melee_attack_handler.h"

#include "map_monitor.h"
#include "server_manager.h"

void run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    MapMonitor& map = server_manager.get_map_by_client(client_id);
    map.push_action(client_id, new ActionAttackMelee());
}
