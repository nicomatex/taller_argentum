#include "receive_handler.h"

#include <iostream>

#include "../nlohmann/json.hpp"
#include "engine/ECS/entity.h"
#include "engine/components/position_component.h"
#include "engine/entity_factory.h"

using json = nlohmann::json;

ClientReceiveHandler::ClientReceiveHandler(MapChangeBuffer &map_change_buffer)
    : map_change_buffer(map_change_buffer) {}

ClientReceiveHandler::~ClientReceiveHandler(){}

void ClientReceiveHandler::handle(Event &ev) {
    json event = ev.get_json();
    switch (int(event["ev_id"])) {
        case 0:
            std::cerr << "Handler: got: " << ev.get_json() << std::endl;
            handle_initialization(ev);
            break;
        case 1:
            handle_new_map(ev);
            break;
        case 2:
            handle_move(ev);
            break;
        case 3:
            // std::cerr << "Handler: got: " << ev.get_json() << std::endl;
            break;
        case -1:
            std::cout << "Fui kickeado del servidor." << std::endl;
    };
}

void ClientReceiveHandler::handle_move(Event &ev) {
    json event = ev.get_json();
    for (auto &it : event["positions"].items()) {
        json entity_position = it.value();
        int entity_id = entity_position["entity_id"];
        int x = entity_position["x"];
        int y = entity_position["y"];
        EntityManager::get_instance()
            .get_from_id(entity_id)
            .get_component<PositionComponent>()
            .set_position(x, y);
    }
}

void ClientReceiveHandler::handle_initialization(Event &ev) {
    json player_info = ev.get_json();
    std::cout << player_info << std::endl;
    EntityFactory::create_player(player_info["player_id"],
                                 player_info["id_head"], player_info["id_body"],
                                 0, 0);
    map_change_buffer.set_follow_entity_id(player_info["player_id"]);
}

void ClientReceiveHandler::handle_new_map(Event &ev) {
    std::cout << "Generando mapa...\n";
    json map_description = ev.get_json();
    map_change_buffer.set_map_info(map_description);
}
