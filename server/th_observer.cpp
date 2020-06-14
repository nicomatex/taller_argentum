#include "th_observer.h"

#include <chrono>

#include "../nlohmann/json.hpp"

ThObserver::ThObserver(Map& map, BlockingThEventHandler& handler)
    : Thread(), running(false), map(map), handler(handler) {}

void ThObserver::run() {
    running = true;
    while (running) {
        // Usar steady_clock
        PositionMap u_map = map.get_position_map();
        nlohmann::json json_update;
        json_update["ev_id"] = 1;
        json_update["entities"] = u_map;
        handler.push_event(Event(json_update));
    }
    /*

    Those methods MUST be in your type's namespace
    (which can be the global namespace), or the library will not be able
    to locate them (namespace/header).

    Those methods MUST be available (e.g., proper headers must be included)
    everywhere you use these conversions.

    Ejemplo con 2 entidades:
    {"entities":[[5,{"pos":[100,90]}],[1,{"pos":[20,20]}]],"ev_id":1}

    */
}

ThObserver::~ThObserver() {}
