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
                                           ChatBuffer &chat_buffer)
    : map_change_buffer(map_change_buffer), chat_buffer(chat_buffer) {}

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
    std::cout << initialization_info << std::endl;
    json player_info = initialization_info["player"];
    EntityFactory::create_player(
        player_info["player_id"], player_info["head_id"],
        player_info["body_id"], player_info["weapon_id"],
        player_info["shield_id"], player_info["helmet_id"],
        player_info["armor_id"]);

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
            EntityFactory::create_player(
                entity_info["entity_id"], entity_info["head_id"],
                entity_info["body_id"], entity_info["weapon_id"],
                entity_info["shield_id"], entity_info["helmet_id"],
                entity_info["armor_id"]);
        } else {
            Entity &entity = EntityManager::get_instance().get_from_id(
                entity_info["entity_id"]);
            entity.get_component<VisualCharacterComponent>().set_body(
                entity_info["body_id"]);
            entity.get_component<VisualCharacterComponent>().set_head(
                entity_info["head_id"]);
            entity.get_component<VisualCharacterComponent>().set_helmet(
                entity_info["helmet_id"]);
            entity.get_component<VisualCharacterComponent>().set_weapon(
                entity_info["weapon_id"]);
            entity.get_component<VisualCharacterComponent>().set_shield(
                entity_info["shield_id"]);
            entity.get_component<VisualCharacterComponent>().set_armor(
                entity_info["armor_id"]);
            
        }
    }
    EntityManager::get_instance().remove_non_updated();
    EntityManager::get_instance().clean();
}

void ClientReceiveHandler::handle_chat_message(Event &ev) {
    chat_buffer.push(ev.get_json()["msg"]);
}