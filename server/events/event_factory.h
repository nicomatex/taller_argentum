#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "../../include/event.h"
#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "../game/position.h"

class EventFactory {
   public:
    static Event initialize_map(const nlohmann::json& map_data,
                                const nlohmann::json& player_data);

    static Event update_map(const nlohmann::json& position_data);

    static Event notify_map_change();

    static Event change_map(ClientId client_id,
                            const nlohmann::json& player_data);

    static Event update_entities(const nlohmann::json& entity_data);

    static Event update_items(const nlohmann::json& items_data);

    static Event chat_message(const std::string& message);

    static Event disconnect();

    static Event drop_client(ClientId client_id);

    static Event dealt_damage(int damage, EntityId to_id);

    static Event received_damage(int damage);

    static Event damage_evaded(EntityId to_id);
    
    static Event evaded_damage();

    static Event inventory_update(const nlohmann::json& inventory_data);

    static Event pickup_event(ClientId client_id);

    static Event drop_event(ClientId client_id, SlotId slot, uint32_t amount);

    static Event unequip_event(ClientId client_id);

    static Event resuscitate_event(ClientId client_id, position_t target);
};

#endif  // EVENT_FACTORY_H
