#ifndef EVENT_H
#define EVENT_H

#include "nlohmann/json.hpp"

enum server_to_client {
    EV_ID_DROP_CLIENT,
    EV_ID_INITIALIZE_MAP,
    EV_ID_UPDATE_MAP,
    EV_ID_UPDATE_ENTITIES,
    EV_ID_UPDATE_LOOT,
    EV_ID_CHAT_MESSAGE,
    EV_ID_NOTIFY_NEW_MAP,
    EV_ID_DEALT_DAMAGE,
    EV_ID_RECEIVED_DAMAGE,
    EV_ID_INVENTORY_UPDATE
};

enum client_to_server {
    EV_ID_DISCONNECT,
    EV_ID_CONNECT,
    EV_ID_CREATE,
    EV_ID_MOVE,
    EV_ID_ATTACK,
    EV_ID_COMMAND,
    EV_ID_INVENTORY,
    EV_ID_PICKUP_LOOT,
    EV_ID_DROP_LOOT
};

enum server_to_self {
    SERVER_DROP_CLIENT = 1000,
    SERVER_CHANGE_MAP = 1001,
    SERVER_UNEQUIP = 1002,
    SERVER_RESUSCITATE = 1003
};

class Event {
   private:
    nlohmann::json json_ev;

   public:
    Event();

    Event(nlohmann::json ev);

    nlohmann::json get_json() const;

    ~Event();
};

#endif  // EVENT_H
