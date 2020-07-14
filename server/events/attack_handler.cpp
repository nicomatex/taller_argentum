#include "attack_handler.h"

#include "../game/actions/action_attack.h"
#include "../server_manager.h"
#include "../session.h"

// Temp
#include <iostream>

AttackHandler::AttackHandler() {}

void AttackHandler::push_event(const Event& event) {
    ClientId client_id = event.get_json()["client_id"];
    ServerManager& server_manager = ServerManager::get_instance();
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionAttack());
}
