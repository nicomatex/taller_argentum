#include "receive_handler.h"

#include <iomanip>
#include <iostream>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "../engine/ECS/entity.h"
#include "../engine/components/position_component.h"
#include "../engine/components/stats_component.h"
#include "../engine/components/visual_character_component.h"
#include "../engine/components/visual_npc_component.h"
#include "../engine/entity_factory.h"
#include "../engine/sound_system.h"

using json = nlohmann::json;

ClientReceiveHandler::ClientReceiveHandler(MapChangeBuffer &map_change_buffer,
                                           ChatBuffer &chat_buffer,
                                           InventoryBuffer &inventory_buffer,
                                           LootBuffer &loot_buffer,
                                           GameStateMonitor &game_state_monitor)
    : map_change_buffer(map_change_buffer),
      chat_buffer(chat_buffer),
      inventory_buffer(inventory_buffer),
      loot_buffer(loot_buffer),
      game_state_monitor(game_state_monitor) {}

ClientReceiveHandler::~ClientReceiveHandler() {}

void ClientReceiveHandler::handle(Event &ev) {
    json event = ev.get_json();
    switch (int(event["ev_id"])) {
        case EV_ID_INITIALIZE_MAP:
            // std::cout << "Recibido mensaje de inicializacion" << std::endl;
            handle_initialization(ev);
            break;
        case EV_ID_UPDATE_MAP:
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
        case EV_ID_INVENTORY_UPDATE:
            handle_inventory_update(ev);
            break;
        case EV_ID_UPDATE_LOOT:
            handle_loot_update(ev);
            break;
        case EV_ID_RECEIVED_DAMAGE:
            handle_incoming_damage(ev);
            break;
        case EV_ID_DEALT_DAMAGE:
            handle_outcoming_damage(ev);
            break;
        case EV_ID_DAMAGE_EVADED:
            handle_outcoming_evaded_damage(ev);
            break;
        case EV_ID_EVADED_DAMAGE:
            handle_incoming_damage_evaded(ev);
            break;
    };
}

void ClientReceiveHandler::handle_move(Event &ev) {
    json event = ev.get_json();
    for (auto &it : event["positions"].items()) {
        json entity_position = it.value();
        int entity_id = entity_position["entity_id"];

        if (!EntityManager::get_instance().has_entity(entity_id)) {
            std::cerr << "Tried to move entity with id " << entity_id
                      << "but it was not found." << std::endl;
            continue;
        }

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
    Entity &player = EntityFactory::create_player(player_info);
    player.get_component<PositionComponent>().set_position(
        player_info["pos"]["x"], player_info["pos"]["y"]);
    std::cout << "Inicializando en posicion " << player_info["pos"]["x"]
              << " - " << player_info["pos"]["y"] << std::endl;

    json map_description = initialization_info["map_info"];
    std::cout << "Recibido nuevo mapa. Llenando " << std::endl;
    map_change_buffer.fill(map_description, player_info["entity_id"]);
    inventory_buffer.push(initialization_info["player"]["inventory"]);
    game_state_monitor.set_game_state(READY_TO_RUN);
}

void ClientReceiveHandler::handle_entity_update(Event &ev) {
    json entities_info = ev.get_json();
    EntityManager::get_instance().update_initialize();
    for (auto &it : entities_info["entities"].items()) {
        json entity_info = it.value();

        if (!EntityManager::get_instance().has_entity(
                entity_info["entity_id"])) {
            switch ((entity_type_t)entity_info["type_id"]) {
                case PLAYER:
                    EntityFactory::create_player(entity_info)
                        .get_component<VisualCharacterComponent>()
                        .set_orientation(entity_info["direction"]);
                    break;
                case MONSTER:
                    std::cerr << "Creating Monster: " << entity_info["name"]
                              << std::endl;
                    EntityFactory::create_npc(entity_info)
                        .get_component<VisualNPCComponent>()
                        .set_orientation(entity_info["direction"]);
                    break;
                case NPC:
                    // todo
                    break;
            }
        } else {
            Entity &entity = EntityManager::get_instance().get_from_id(
                entity_info["entity_id"]);
            switch ((entity_type_t)entity_info["type_id"]) {
                case PLAYER:
                    entity.get_component<VisualCharacterComponent>()
                        .server_update(entity_info);
                    entity.get_component<StatsComponent>().server_update(
                        entity_info);
                    break;
                case MONSTER:
                    entity.get_component<VisualNPCComponent>().server_update(
                        entity_info);
                    break;
                case NPC:
                    // todo
                    break;
            }
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

void ClientReceiveHandler::handle_inventory_update(Event &ev) {
    inventory_buffer.push(ev.get_json()["inventory"]);
}

void ClientReceiveHandler::handle_loot_update(Event &ev) {
    loot_buffer.load_buffer(ev.get_json());
}

void ClientReceiveHandler::handle_incoming_damage(Event &ev) {
    SoundSystem::get_instance().play_game_sfx(5);
    int player_id = map_change_buffer.get_follow_entity_id();
    EntityManager::get_instance()
        .get_from_id(player_id)
        .get_component<VisualCharacterComponent>()
        .display_damage(ev.get_json()["dmg"]);
}

void ClientReceiveHandler::handle_outcoming_damage(Event &ev) {
    SoundSystem::get_instance().play_game_sfx(4);
}

void ClientReceiveHandler::handle_outcoming_evaded_damage(Event &ev) {
    SoundSystem::get_instance().play_game_sfx(6);
}

void ClientReceiveHandler::handle_incoming_damage_evaded(Event &ev) {
    SoundSystem::get_instance().play_game_sfx(7);
}