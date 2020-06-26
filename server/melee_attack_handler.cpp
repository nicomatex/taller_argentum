#include "melee_attack_handler.h"

#include "action_melee_attack.h"
#include "map_monitor.h"
#include "server_manager.h"

MeleeAttackHandler::MeleeAttackHandler(Event& ev) : ThEventHandler(ev) {}
MeleeAttackHandler::~MeleeAttackHandler() {}

void MeleeAttackHandler::run_handler() {
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    MapMonitor& map = server_manager.get_map_by_client(client_id);
    map.push_action(client_id, new ActionMeleeAttack());
}
