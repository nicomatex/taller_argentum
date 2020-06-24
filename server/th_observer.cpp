#include "th_observer.h"

#include <chrono>
#include <iostream>

#include "../nlohmann/json.hpp"
#include "event_factory.h"
#include "server_manager.h"

constexpr std::chrono::milliseconds OBSERVER_INTERVAL(5);

ThObserver::ThObserver(MapMonitor& map_monitor, BlockingThEventHandler& handler)
    : Thread(),
      running(false),
      map(map_monitor),
      handler(handler),
      update_entities(false) {}

void ThObserver::run() {
    try {
        running = true;
        int counter = 0;
        while (running) {
            auto start = std::chrono::steady_clock::now();
            if (++counter % 10 == 0 || update_entities) {
                update_entities = true;
                counter = 0;
            }
            bool aux = update_entities;
            nlohmann::json map_data = map.get_update_data(aux);
            update_entities = aux;
            if (update_entities) {
                update_entities = false;
                handler.push_event(
                    EventFactory::update_entities(map_data["entities"]));
            }
            handler.push_event(EventFactory::update_map(map_data["positions"]));
            auto dif =
                OBSERVER_INTERVAL - (std::chrono::steady_clock::now() - start);
            sleep(dif);
        }
    } catch (const std::exception& e) {
        std::cerr << "Observer: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Observer: Unknown exception" << std::endl;
    }
    std::cout << "Observer finished" << std::endl;
}

void ThObserver::stop() {
    running = false;
}

void ThObserver::refresh_entities() {
    update_entities = true;
}

ThObserver::~ThObserver() {}
