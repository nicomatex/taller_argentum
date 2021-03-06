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

    static Event notify_new_map();

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

    static Event unequip_all_event(ClientId client_id);

    static Event resuscitate_event(ClientId client_id);

    static Event heal_event(ClientId client_id, position_t target);

    static Event name_not_found();

    static Event name_already_online();

    static Event name_taken();

    static Event sell_event(ClientId client_id, position_t target, SlotId slot,
                            uint32_t amount);

    static Event buy_event(ClientId client_id, position_t target, SlotId slot,
                           uint32_t amount);

    static Event list_event(ClientId client_id, position_t target);

    static Event special_ability(const nlohmann::json& cast_info);

    static Event deposit_item_event(ClientId client_id, position_t target,
                                    SlotId slot, uint32_t amount);

    static Event withdraw_item_event(ClientId client_id, position_t target,
                                    SlotId slot, uint32_t amount);

    static Event deposit_gold_event(ClientId client_id, position_t target, uint32_t amount);

    static Event withdraw_gold_event(ClientId client_id, position_t target, uint32_t amount);
    
    static Event meditate_event(ClientId client_id);

    static Event resuscitate();
};

#endif  // EVENT_FACTORY_H
