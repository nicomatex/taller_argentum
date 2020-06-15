#include "receive_handler.h"
#include "../nlohmann/json.hpp"
#include "engine/ECS/entity.h"
#include "engine/components/position_component.h"

using json = nlohmann::json;

ClientReceiveHandler::ClientReceiveHandler(EntityManager &entity_manager, Map &map)
    : entity_manager(entity_manager),map(map) {}

void ClientReceiveHandler::handle(Event& ev){
    json event = ev.get_json();
    if(int(event["ev_id"]) == 3) handle_new_map(ev);
}

void ClientReceiveHandler::handle_new_map(Event &ev){
    json map_description = ev.get_json()["map"];
    map.generate(map_description);
}