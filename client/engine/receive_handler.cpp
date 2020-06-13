#include "receive_handler.h"
#include "json.hpp"
#include "ECS/entity.h"
#include "components/position_component.h"

using json = nlohmann::json;

ClientHandler::ClientHandler(EntityManager &entity_manager)
    : entity_manager(entity_manager) {}

void ClientHandler::handle(Event& ev){
    json event = ev.get_json();
    unsigned int new_x = event["x"];
    unsigned int new_y = event["y"];
    entity_manager.get_from_id(1).get_component<PositionComponent>().set_position(new_x,new_y);
}