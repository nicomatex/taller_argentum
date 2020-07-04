#include "event_factory.h"
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

Event EventFactory::chat_event(std::string message) {
    json event = {{"ev_id", EV_ID_COMMAND}, {"msg", message}};
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

Event EventFactory::inventory_event(SlotId slot){
    json event = {{"ev_id",EV_ID_INVENTORY},{"slot",slot}};
    return Event(event);
}