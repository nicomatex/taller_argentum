#include "receive_handler.h"

#include <iostream>

#include "../nlohmann/json.hpp"
#include "engine/ECS/entity.h"
#include "engine/components/position_component.h"

using json = nlohmann::json;

ClientReceiveHandler::ClientReceiveHandler(EntityManager &entity_manager,
                                           Map &map, std::atomic_bool &ready,
                                           std::atomic_bool &running)
    : entity_manager(entity_manager),
      map(map),
      ready(ready),
      running(running) {}

void ClientReceiveHandler::handle(Event &ev) {
    json event = ev.get_json();
    switch (int(event["ev_id"])) {
        case 1:
            handle_new_map(ev);
            break;
        case 2:
            handle_move(ev);
            break;
        case 3:
            std::cerr << "Handler: got: " << ev.get_json() << std::endl;
            break;
        case -1:
            std::cout << "Fui kickeado del servidor." << std::endl;
            running = false;
    };
}

void ClientReceiveHandler::handle_move(Event &ev) {
    json event = ev.get_json();
    for (auto &it : event["positions"].items()) {
        json entity_position = it.value();
        int entity_id = entity_position["entity_id"];
        int x = entity_position["x"];
        int y = entity_position["y"];
        entity_manager.get_from_id(entity_id)
            .get_component<PositionComponent>()
            .set_position(x, y);
    }
}

void ClientReceiveHandler::handle_new_map(Event &ev) {
    std::cout << "Generando mapa...\n";
    json map_description = ev.get_json();
    map.generate(map_description);
    ready = true;
}