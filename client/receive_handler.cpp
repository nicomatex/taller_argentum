#include "receive_handler.h"

#include <iomanip>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "engine/ECS/entity.h"
#include "engine/components/position_component.h"
#include "engine/components/stats_component.h"
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
        case EV_ID_INITIALIZE_MAP:
            // std::cout << "Recibido mensaje de inicializacion" << std::endl;
            handle_initialization(ev);
            break;
        case EV_ID_MOVE:
            // std::cout << "Recibido evento de movimiento" << std::endl;
            handle_move(ev);
            break;
        case EV_ID_UPDATE_ENTITIES:
            // std::cout << "Recibido evento de update entities" << std::endl;
            handle_entity_update(ev);
            break;
        case EV_ID_CHAT_MESSAGE:
            // std::cout << "Recibido evento de chat " << std::endl;
            handle_chat_message(ev);
            break;
        case EV_ID_NOTIFY_NEW_MAP:
            // std::cout << "Recibida notificacion de nuevo mapa " << std::endl;
            handle_map_change(ev);
            break;
        case EV_ID_DISCONNECT:
            std::cout << "Fui kickeado del servidor." << std::endl;
            game_state_monitor.quit();
            break;
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
    game_state_monitor.wait_for_game_state(WAITING_FOR_INITIALIZATION);
    json initialization_info = ev.get_json();
    json player_info = initialization_info["player"];
    player_info["entity_id"] = player_info["player_id"];
    Entity &player = EntityFactory::create_player(player_info);
    player.get_component<PositionComponent>().set_position(
        player_info["pos"]["x"], player_info["pos"]["y"]);
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
            entity.get_component<StatsComponent>().set_stat_max_value(
                "hp", entity_info["max_hp"]);
            entity.get_component<StatsComponent>().set_stat_current_value(
                "hp", entity_info["curr_hp"]);
        }
    }

    EntityManager::get_instance().remove_non_updated();
    EntityManager::get_instance().clean();
}

void ClientReceiveHandler::handle_chat_message(Event &ev) {
    chat_buffer.push(ev.get_json()["msg"]);
}

void ClientReceiveHandler::handle_map_change(Event &ev) {
    map_change_buffer.reset();
    game_state_monitor.set_game_state(SWITCHING_MAPS);
    std::cout << "Cargando nuevo mapa..." << std::endl;
}