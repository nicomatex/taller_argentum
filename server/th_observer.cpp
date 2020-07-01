#include "th_observer.h"

#include <chrono>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "events/event_factory.h"
#include "server_manager.h"

#define ENTITY_UPDATE_INTERVAL 10

constexpr std::chrono::milliseconds OBSERVER_INTERVAL(5);

ThObserver::ThObserver(MapMonitor& map_monitor, BlockingThEventHandler& handler)
    : Thread(),
      running(false),
      map(map_monitor),
      handler(handler),
      update_entities(false) {}

void ThObserver::send_update_logs() {
    ServerManager& server_manager = ServerManager::get_instance();
    std::vector<nlohmann::json> logs = map.get_update_logs();
    for (auto& it : logs) {
        try {
            server_manager.send_to(
                server_manager.get_client_by_name(it["player_name"]),
                EventFactory::chat_message(it["str"]));
        } catch (const std::exception& e) {
            std::cerr << it << std::endl;
        }
    }
}

void ThObserver::run() {
    try {
        running = true;
        int counter = 0;
        while (running) {
            auto start = std::chrono::steady_clock::now();
            if (update_entities || ++counter % ENTITY_UPDATE_INTERVAL == 0) {
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
            send_update_logs();
            auto dif =
                OBSERVER_INTERVAL - (std::chrono::steady_clock::now() - start);
            sleep(dif);
        }
    } catch (const std::exception& e) {
        std::cerr << "Observer: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Observer: Unknown exception" << std::endl;
    }
    std::cerr << "Observer finished" << std::endl;
}

void ThObserver::stop() {
    running = false;
}

void ThObserver::refresh_entities() {
    update_entities = true;
}

ThObserver::~ThObserver() {}
