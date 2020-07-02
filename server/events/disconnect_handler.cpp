#include "disconnect_handler.h"

#include "../../include/nlohmann/json.hpp"
#include "../server_manager.h"

DisconnectHandler::DisconnectHandler() {}
DisconnectHandler::~DisconnectHandler() {}

void DisconnectHandler::push_event(const Event& event) {
    nlohmann::json json_ev = event.get_json();
    ServerManager::get_instance().drop_client(json_ev["client_id"]);
}
