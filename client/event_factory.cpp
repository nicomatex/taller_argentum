#include "event_factory.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

EventFactory::EventFactory(){}

EventFactory::~EventFactory(){}

Event EventFactory::connect_event(std::string character_name, std::string password){
    json event = 
    {
        {"ev_id",0},
        {"player",
            {
                {"name",character_name},
                {"password",password}
            }
        }
    };
    return Event(event);
}

Event EventFactory::console_command_event(std::string command,std::vector<std::string> args){
    json event = 
    {
        {"ev_id",1},
        {"command",
            {
                {"cmd",command},
                {"args",args}
            }
        }
    };
    return Event(event);
}

Event EventFactory::movement_event(movement_action_t action, direction_t direction){
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
    return Event(event);
}

