#include "th_observer.h"

#include <chrono>
#include <iostream>

#include "../nlohmann/json.hpp"

constexpr std::chrono::milliseconds OBSERVER_INTERVAL(15);

ThObserver::ThObserver(Map& map, BlockingThEventHandler& handler)
    : Thread(), running(false), map(map), handler(handler) {}

void ThObserver::run() {
    try {
        running = true;
        int counter = 0;
        while (running) {
            auto start = std::chrono::steady_clock::now();
            nlohmann::json json_update;
            if (++counter % 5 == 0) {
                counter = 0;
                // nlohmann::json json_entities = map.get_entity_data();
                // json_entities["ev_id"] = 2;
                // handler.push_event(Event(json_entities));
            } else {
                json_update = map.get_position_data();
                json_update["ev_id"] = 1;
            }
            sleep(OBSERVER_INTERVAL -
                  (std::chrono::steady_clock::now() - start));
            handler.push_event(Event(json_update));
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

ThObserver::~ThObserver() {}
