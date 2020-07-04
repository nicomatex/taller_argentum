#include "event_factory.h"

#include <iostream>  //temp
#include <string>

Event EventFactory::initialize_map(const nlohmann::json& map_data,
                                   const nlohmann::json& player_data) {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_INITIALIZE_MAP;
    ev_json["map_info"] = map_data;
    ev_json["player"] = player_data;
    return Event(ev_json);
}

Event EventFactory::update_map(const nlohmann::json& position_data) {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_UPDATE_MAP;
    ev_json["positions"] = position_data;
    return Event(ev_json);
}

Event EventFactory::notify_map_change() {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_NOTIFY_NEW_MAP;
    return Event(ev_json);
}

Event EventFactory::change_map(ClientId client_id,
                               const nlohmann::json& player_data) {
    nlohmann::json ev_json;
    ev_json["ev_id"] = SERVER_CHANGE_MAP;
    ev_json["client_id"] = client_id;
    ev_json["player_info"] = player_data;
    return Event(ev_json);
}

Event EventFactory::update_entities(const nlohmann::json& entity_data) {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_UPDATE_ENTITIES;
    ev_json["entities"] = entity_data;
    return Event(ev_json);
}

Event EventFactory::chat_message(const std::string& message) {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_CHAT_MESSAGE;
    ev_json["msg"] = message;
    return Event(ev_json);
}

Event EventFactory::disconnect() {
    nlohmann::json ev_json;
    ev_json["ev_id"] = EV_ID_DROP_CLIENT;
    return Event(ev_json);
}

Event EventFactory::drop_client(ClientId client_id) {
    nlohmann::json ev_json = {{"ev_id", SERVER_DROP_CLIENT},
                              {"client_id", client_id}};
    return Event(ev_json);
}

Event EventFactory::dealt_damage(int damage, EntityId to_id) {
    nlohmann::json ev_json = {
        {"ev_id", EV_ID_DEALT_DAMAGE}, {"dmg", damage}, {"to", to_id}};
    return Event(ev_json);
}

Event EventFactory::received_damage(int damage) {
    nlohmann::json ev_json = {{"ev_id", EV_ID_RECEIVED_DAMAGE},
                              {"dmg", damage}};
    return Event(ev_json);
}

Event EventFactory::inventory_update(const nlohmann::json& inventory_data) {
    nlohmann::json ev_json = {{"ev_id", EV_ID_INVENTORY_UPDATE},
                              {"inventory", inventory_data}};
    return Event(ev_json);
}