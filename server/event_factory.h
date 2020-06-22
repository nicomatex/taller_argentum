#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "../include/event.h"
#include "../include/types.h"
#include "../nlohmann/json.hpp"

class EventFactory {
   public:
    static Event initialize_map(const nlohmann::json& map_data,
                                const nlohmann::json& player_data);

    static Event update_map(const nlohmann::json& position_data);

    static Event update_entities(const nlohmann::json& entity_data);

    static Event chat_message(const std::string& message);

    static Event drop_client(ClientId client_id);
};

#endif  // EVENT_FACTORY_H
