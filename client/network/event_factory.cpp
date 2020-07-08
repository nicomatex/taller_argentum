#include "event_factory.h"

#include <iostream>

#include "../../include/nlohmann/json.hpp"

using json = nlohmann::json;

EventFactory::EventFactory() {}

EventFactory::~EventFactory() {}

/*No aplicarle el auto-estilizador a este archivo porque se desacomodan los
 * json*/

Event EventFactory::connect_event(std::string character_name,
                                  std::string password) {
    json event = {
        {"ev_id", EV_ID_CONNECT},
        {"player", {{"name", character_name}, {"password", password}}}};
    return Event(event);
}

Event EventFactory::chat_event(std::string message, int target_x, int target_y,
                               int inventory_slot) {
    json event = {{"ev_id", EV_ID_COMMAND},
                  {"msg", message},
                  {"target", {{"x", target_x}, {"y", target_y}}},
                  {"slot", inventory_slot}};

    std::cout << "Generating chat event, with target position " << target_x
              << " - " << target_y << std::endl;
    std::cout << "And target inventory slot " << inventory_slot << std::endl;
    return Event(event);
}

Event EventFactory::movement_event(mov_action_t action, direction_t direction) {
    json event = {{"ev_id", EV_ID_MOVE},
                  {"movement", {{"action", action}, {"direction", direction}}}};
    return Event(event);
}

Event EventFactory::disconnect() {
    json event = {{"ev_id", EV_ID_DISCONNECT}};
    return Event(event);
}

Event EventFactory::attack_event() {
    json event = {{"ev_id", EV_ID_ATTACK}};
    return Event(event);
}

Event EventFactory::inventory_event(SlotId slot) {
    json event = {{"ev_id", EV_ID_INVENTORY}, {"slot", slot}};
    return Event(event);
}

Event EventFactory::create_event(std::string name, class_type_t class_type,
                                 race_type_t race_type) {
    json event = {{"ev_id", EV_ID_CREATE},
                  {"name", name},
                  {"class_type", class_type},
                  {"race_type", race_type}};
    return Event(event);
}

Event EventFactory::pickup_event() {
    json event = {{"ev_id", EV_ID_PICKUP_LOOT}};
    return Event(event);
}

Event EventFactory::drop_item_event(SlotId slot) {
    json event = {{"ev_id", EV_ID_DROP_LOOT}, {"slot", slot}};
    return Event(event);
}

Event EventFactory::unequip_event(SlotId slot) {
    json event = {{"ev_id", EV_ID_UNEQUIP}, {"slot", slot}};
    return Event(event);
}
