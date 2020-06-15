#include "movement_handler.h"
#include <iostream> //TODO: SACAR DESP

MovementHandler::MovementHandler(Event ev, ServerManager& server_manager) :
ThEventHandler(ev),
server_manager(server_manager) {}

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
	nlohmann::json movement_info = event.get_json();
	int client_id = movement_info["client_id"];
	mov_action_t mov_act = movement_info["action"];
	direction_t direction = movement_info["direction"];
	Player& player = server_manager.getPlayer(client_id);
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
			case default:
				std::cerr << "Error json: " << movement_info << std::endl;
				break;
		}
	}
}
