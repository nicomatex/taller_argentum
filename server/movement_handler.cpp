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
    if (mov_act == STOP) {
        map_monitor.with_player(client_id, ActionMove(0, 0));
    } else {
        switch (direction) {
            case UP:
                std::cout << "\tUP" << std::endl;
                map_monitor.with_player(client_id, ActionMove(0, -1));
                break;
            case DOWN:
                std::cout << "\tDOWN" << std::endl;
                map_monitor.with_player(client_id, ActionMove(0, 1));
                break;
            case RIGHT:
                std::cout << "\tRIGHT" << std::endl;
                map_monitor.with_player(client_id, ActionMove(1, 0));
                break;
            case LEFT:
                std::cout << "\tLEFT" << std::endl;
                map_monitor.with_player(client_id, ActionMove(-1, 0));
                break;
            default:
                std::cerr << "Error json: " << movement_info << std::endl;
                break;
        }
    }
}
