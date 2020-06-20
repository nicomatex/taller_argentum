#include "th_observer.h"

#include <chrono>
#include <iostream>

#include "../nlohmann/json.hpp"
#include "server_manager.h"

constexpr std::chrono::milliseconds OBSERVER_INTERVAL(5);

ThObserver::ThObserver(MapMonitor& map_monitor, BlockingThEventHandler& handler)
    : Thread(), running(false), map(map_monitor), handler(handler) {}

void ThObserver::run() {
    try {
        running = true;
        int counter = 0;
        while (running) {
            auto start = std::chrono::steady_clock::now();
            nlohmann::json json_update;
            if (++counter % 5 == 0) {
                counter = 0;
                nlohmann::json json_entities;
                json_entities["entities"] = map.get_entity_data();
                json_entities["ev_id"] = 3;
                handler.push_event(Event(json_entities));
            }
            json_update["positions"] = map.get_position_data();
            json_update["ev_id"] = 2;
            auto dif =
                OBSERVER_INTERVAL - (std::chrono::steady_clock::now() - start);
            sleep(dif);
            handler.push_event(Event(json_update));
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Observer finished" << std::endl;
}

void ThObserver::stop() {
    running = false;
}

ThObserver::~ThObserver() {}
