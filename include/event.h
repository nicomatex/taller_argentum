#ifndef EVENT_H
#define EVENT_H

#include "../nlohmann/json.hpp"

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
