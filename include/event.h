#ifndef EVENT_H
#define EVENT_H

#include "nlohmann/json.hpp"

enum server_to_client {
    EV_ID_DROP_CLIENT = -1,
    EV_ID_INITIALIZE_MAP = 0,
    EV_ID_UPDATE_MAP = 2,
    EV_ID_UPDATE_ENTITIES = 3,
    EV_ID_CHAT_MESSAGE = 4,
    EV_ID_NOTIFY_NEW_MAP = 5,
    EV_ID_DEALT_DAMAGE = 6,
    EV_ID_RECEIVED_DAMAGE = 7,
    EV_ID_INVENTORY_UPDATE
};

enum client_to_server {
    EV_ID_DISCONNECT = -1,
    EV_ID_CONNECT = 0,
    EV_ID_CREATE = 1,
    EV_ID_MOVE = 2,
    EV_ID_ATTACK = 3,
    EV_ID_COMMAND = 4
};

enum server_to_self { SERVER_DROP_CLIENT = -2, SERVER_CHANGE_MAP = 10 };

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
