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
    return Event({"ev_id", EV_ID_DISCONNECT});
}

Event EventFactory::drop_client(ClientId client_id) {
    return Event({{"ev_id", EV_ID_DROP_CLIENT}, {"client_id", client_id}});
}
