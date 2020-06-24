#include "movement_handler.h"

#include <iostream>  //TODO: SACAR DESP

#include "action_move.h"
#include "map_monitor.h"
#include "server_manager.h"

MovementHandler::MovementHandler(Event ev) : ThEventHandler(ev) {}

MovementHandler::~MovementHandler() {}

void MovementHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json movement_info = event.get_json();
    ClientId client_id = movement_info["client_id"];
    mov_action_t mov_act = movement_info["movement"]["action"];
    direction_t direction = movement_info["movement"]["direction"];
    MapMonitor& map_monitor = server_manager.get_map_by_client(client_id);
    map_monitor.with_player(client_id, ActionMove(mov_act, direction));
}
