#include "receive_handler.h"

#include <iomanip>
#include <iostream>

#include "../nlohmann/json.hpp"
#include "engine/ECS/entity.h"
#include "engine/components/position_component.h"
#include "engine/components/visual_character_component.h"
#include "engine/entity_factory.h"

using json = nlohmann::json;

ClientReceiveHandler::ClientReceiveHandler(MapChangeBuffer &map_change_buffer,
                                           ChatBuffer &chat_buffer,
                                           GameStateMonitor &game_state_monitor)
    : map_change_buffer(map_change_buffer),
      chat_buffer(chat_buffer),
      game_state_monitor(game_state_monitor) {}

ClientReceiveHandler::~ClientReceiveHandler() {}

void ClientReceiveHandler::handle(Event &ev) {
    json event = ev.get_json();
    switch (int(event["ev_id"])) {
        case 0:
            handle_initialization(ev);
            break;
        case 2:
            handle_move(ev);
            break;
        case 3:
            handle_entity_update(ev);
            break;
        case 4:
            handle_chat_message(ev);
            break;
        case -1:
            std::cout << "Fui kickeado del servidor." << std::endl;
            game_state_monitor.quit();
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
    json initialization_info = ev.get_json();
    json player_info = initialization_info["player"];
    player_info["entity_id"] = player_info["player_id"];
    EntityFactory::create_player(player_info);

    json map_description = initialization_info["map_info"];
    map_change_buffer.fill(map_description, player_info["player_id"]);
}

void ClientReceiveHandler::handle_entity_update(Event &ev) {
    json entities_info = ev.get_json();
    EntityManager::get_instance().update_initialize();
    for (auto &it : entities_info["entities"].items()) {
        json entity_info = it.value();
        if (!EntityManager::get_instance().has_entity(
                entity_info["entity_id"])) {
            Entity &new_player = EntityFactory::create_player(entity_info);
            new_player.get_component<VisualCharacterComponent>()
                .set_orientation(entity_info["direction"]);
        } else {
            Entity &entity = EntityManager::get_instance().get_from_id(
                entity_info["entity_id"]);
            entity.get_component<VisualCharacterComponent>().server_update(
                entity_info);
        }
    }
    EntityManager::get_instance().remove_non_updated();
    EntityManager::get_instance().clean();
}

void ClientReceiveHandler::handle_chat_message(Event &ev) {
    chat_buffer.push(ev.get_json()["msg"]);
}