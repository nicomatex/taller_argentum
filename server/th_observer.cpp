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
      forced_update(false) {}

void ThObserver::send_update_logs() {
    ServerManager& server_manager = ServerManager::get_instance();
    std::vector<map_log_t> logs = map.get_update_logs();
    for (auto& log : logs) {
        try {
            ClientId client_id =
                server_manager.get_client_by_name(log.player_name);
            switch (log.type) {
                case LOG_DEAL_DAMAGE: {
                    int dmg = log.info["damage"];
                    const std::string& to = log.info["to"];
                    // server_manager.send_to(
                    //     client_id,
                    //     EventFactory::dealt_damage(dmg, it["to_id"]));
                    std::string msg =
                        "Hecho " + std::to_string(dmg) + " de danio a " + to;
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));
                } break;
                case LOG_RECV_DAMAGE: {
                    int dmg = log.info["damage"];
                    const std::string& from = log.info["from"];
                    // server_manager.send_to(client_id,
                    //                        EventFactory::received_damage(dmg));
                    std::string msg = "Recibido " + std::to_string(dmg) +
                                      " de danio por " + from;
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));
                } break;
                case LOG_INVENTORY: {
                    server_manager.send_to(
                        client_id,
                        EventFactory::inventory_update(log.info["inventory"]));
                } break;
                default:
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Observer: update_logs error: type " << log.type
                      << " info: " << log.info << std::endl;
        }
    }
}

void ThObserver::run() {
    running = true;
    int counter = 0;
    // bool dirty_entities = false;
    // bool dirty_loot = false;
    while (running) {
        try {
            auto start = std::chrono::steady_clock::now();
            // dirty_entities = map.dirty_entities();
            // dirty_loot = map.dirty_loot();
            if (forced_update || ++counter % ENTITY_UPDATE_INTERVAL == 0) {
                forced_update = true;
                counter = 0;
            }
            nlohmann::json map_data = map.get_update_data(forced_update);
            if (forced_update || map_data.contains("entities")) {
                forced_update = false;
                handler.push_event(
                    EventFactory::update_entities(map_data["entities"]));
            }
            if (map_data.contains("items") && !map_data["items"].empty()) {
                forced_update = false;
                std::cout << "Sending loot data" << std::endl;
                std::cout << map_data["items"] << std::endl;
                handler.push_event(
                    EventFactory::update_items(map_data["items"]));
            }
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

ThObserver::~ThObserver() {}
