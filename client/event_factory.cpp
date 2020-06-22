#include "event_factory.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

EventFactory::EventFactory(){}

EventFactory::~EventFactory(){}

/*No aplicarle el auto-estilizador a este archivo porque se desacomodan los json*/

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

Event EventFactory::chat_event(std::string message){
    json event = 
    {
        {"ev_id",4},
        {"msg",message}
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

Event EventFactory::drop_event(){
    json event = 
    {
        {"ev_id",-1}
    };
    return  Event(event);
}

