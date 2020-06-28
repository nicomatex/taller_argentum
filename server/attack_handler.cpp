#include "attack_handler.h"

#include "action_attack.h"
#include "map_monitor.h"
#include "server_manager.h"

// Temp
#include <iostream>

void AttackHandler::run_handler() {
    std::cerr << "AttackHandler: " << event.get_json() << std::endl;
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    MapMonitor& map = server_manager.get_map_by_client(client_id);
    map.push_action(client_id, new ActionAttack());
}

AttackHandler::AttackHandler(Event& ev) : ThEventHandler(ev) {}
AttackHandler::~AttackHandler() {}
