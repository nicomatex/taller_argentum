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
      added_client(false) {}

void ThObserver::send_update_logs() {
    ServerManager& server_manager = ServerManager::get_instance();
    std::vector<nlohmann::json> logs = map.get_update_logs();
    for (auto& it : logs) {
        try {
            ClientId client_id =
                server_manager.get_client_by_name(it["player_name"]);
            int log_type = it["log_type"];
            switch (log_type) {
                case 1: {
                    int dmg = it["damage"];
                    const std::string& to = it["to"];
                    // server_manager.send_to(
                    //     client_id,
                    //     EventFactory::dealt_damage(dmg, it["to_id"]));
                    std::string msg =
                        "Hecho " + std::to_string(dmg) + " de danio a " + to;
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));
                } break;
                case 2: {
                    int dmg = it["damage"];
                    const std::string& from = it["from"];
                    // server_manager.send_to(client_id,
                    //                        EventFactory::received_damage(dmg));
                    std::string msg = "Recibido " + std::to_string(dmg) +
                                      " de danio por " + from;
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));
                } break;
                case 3: {
                    server_manager.send_to(
                        client_id,
                        EventFactory::inventory_update(it["inventory"]));
                } break;
                default:
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Observer: update_logs: " << it << std::endl;
        }
    }
}

void ThObserver::run() {
    running = true;
    int counter = 0;
    bool dirty_entities = false;
    bool dirty_loot = false;
    while (running) {
        try {
            auto start = std::chrono::steady_clock::now();
            dirty_entities = map.dirty_entities();
            dirty_loot = map.dirty_loot();
            if (++counter % ENTITY_UPDATE_INTERVAL == 0) {
                added_client = true;
                counter = 0;
            }
            nlohmann::json map_data = map.get_update_data();
            if ((added_client || dirty_entities) && !map_data["entities"].empty()) {
                handler.push_event(
                    EventFactory::update_entities(map_data["entities"]));
            }
            if ((added_client || dirty_loot) && !map_data["items"].empty()) {
                std::cerr << "Observer: items: " << map_data["items"]
                          << std::endl;
                handler.push_event(
                    EventFactory::update_items(map_data["items"]));
            }
            added_client = false;
            handler.push_event(EventFactory::update_map(map_data["positions"]));
            send_update_logs();
            auto dif =
                OBSERVER_INTERVAL - (std::chrono::steady_clock::now() - start);
            sleep(dif);
        } catch (const std::exception& e) {
            std::cerr << "Observer: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Observer: Unknown exception" << std::endl;
        }
    }
    std::cerr << "Observer finished" << std::endl;
}

void ThObserver::stop() {
    running = false;
}

void ThObserver::refresh_entities() {
    added_client = true;
}

ThObserver::~ThObserver() {}
