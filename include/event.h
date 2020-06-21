#ifndef EVENT_H
#define EVENT_H

#include "../nlohmann/json.hpp"

enum server_to_client {
    EV_ID_INITIALIZE_MAP = 0,
    EV_ID_UPDATE_MAP = 2,
    EV_ID_UPDATE_ENTITIES = 3,
    EV_ID_CHAT_MESSAGE = 4
};

enum client_to_server {
    EV_ID_CONNECT_EVENT = 0,
    EV_ID_MOVE_EVENT = 2,
    EV_ID_COMMAND = 4
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
