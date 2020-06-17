#include "movement_handler.h"

#include <iostream>  //TODO: SACAR DESP

#include "server_manager.h"

MovementHandler::MovementHandler(Event ev) : ThEventHandler(ev) {}

MovementHandler::~MovementHandler() {}

/*
    Supongo que también tiene un client_id que se lo agrega el receiver..
    json event =
    {
        {"ev_id",2},
        {"movement",
            {
                {"action",action},
                {"direction",direction}
            }
        }
    };

*/

void MovementHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json movement_info = event.get_json();
    ClientId client_id = movement_info["client_id"];
    mov_action_t mov_act = movement_info["movement"]["action"];
    direction_t direction = movement_info["movement"]["direction"];
    Player& player = server_manager.get_player(client_id);
    if (mov_act == STOP) {
        player.set_current_speed(0, 0);
    } else {
        switch (direction) {
            case UP:
                std::cout << "UP" << std::endl;
                player.set_current_speed(0, 1);
                break;
            case DOWN:
                std::cout << "DOWN" << std::endl;
                player.set_current_speed(0, -1);
                break;
            case RIGHT:
                std::cout << "RIGHT" << std::endl;
                player.set_current_speed(1, 0);
                break;
            case LEFT:
                std::cout << "LEFT" << std::endl;
                player.set_current_speed(-1, 0);
                break;
            default:
                std::cerr << "Error json: " << movement_info << std::endl;
                break;
        }
    }
}
