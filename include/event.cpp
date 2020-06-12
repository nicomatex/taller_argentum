#include "event.h"

Event::Event() {}

Event::Event(nlohmann::json ev) : json_ev(ev) {}

nlohmann::json Event::get_json() const {
    return json_ev;
}

Event::~Event() {}
