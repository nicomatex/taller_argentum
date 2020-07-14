#include "movement_handler.h"

#include "../../include/types.h"
#include "../game/actions/action_move.h"
#include "../server_manager.h"
#include "../session.h"

// Temp
#include <iostream>

MovementHandler::MovementHandler() {}

void MovementHandler::push_event(const Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json movement_info = event.get_json();
    ClientId client_id = movement_info["client_id"];
    mov_action_t mov_act = movement_info["movement"]["action"];
    direction_t direction = movement_info["movement"]["direction"];
    Session& session = server_manager.get_session(client_id);
    session.push_action(client_id, new ActionMove(mov_act, direction));
}
