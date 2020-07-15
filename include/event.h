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
    EV_ID_INVENTORY_UPDATE,
    EV_ID_EVADED_DAMAGE,
    EV_ID_DAMAGE_EVADED,
    EV_ID_NAME_NOTFOUND,
    EV_ID_NAME_TAKEN,
    EV_ID_SPECIAL_ABILITY,
    EV_ID_NAME_ALREADY_ONLINE
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
    EV_ID_DROP_LOOT,
    EV_ID_USE_ABILITY,
    EV_ID_UNEQUIP
};

enum server_to_self {
    SERVER_DROP_CLIENT = 1000,
    SERVER_CHANGE_MAP = 1001,
    SERVER_RESUSCITATE = 1003,
    SERVER_HEAL = 1004,
    SERVER_SELL = 1005,
    SERVER_BUY = 1006,
    SERVER_LIST = 1007,
    SERVER_DEPOSIT_ITEM = 1008,
    SERVER_WITHDRAW_ITEM = 1009,
    SERVER_DEPOSIT_GOLD = 1010,
    SERVER_WITHDRAW_GOLD = 1011,
    SERVER_MEDITATE = 1012
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
