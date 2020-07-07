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
                    std::string msg;
                    const std::string& to = log.info["to"];
                    if (!log.info["dodged"]) {
                        int dmg = log.info["damage"];

                        server_manager.send_to(
                            client_id,
                            EventFactory::dealt_damage(dmg, log.info["to_id"]));
                        msg = "Hecho " + std::to_string(dmg) + " de danio a " +
                              to;

                    } else {
                        msg = "Me ha evadido el golpe " + to;
                    }
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));

                } break;
                case LOG_RECV_DAMAGE: {
                    std::string msg;
                    const std::string& from = log.info["from"];
                    if (!log.info["dodged"]) {
                        int dmg = log.info["damage"];
                        server_manager.send_to(
                            client_id, EventFactory::received_damage(dmg));
                        msg = "Recibido " + std::to_string(dmg) +
                              " de danio por " + from;
                    } else {
                        msg = "He evadido el golpe de " + from;
                    }

                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(msg));
                } break;
                case LOG_INVENTORY:
                    server_manager.send_to(
                        client_id,
                        EventFactory::inventory_update(log.info["inventory"]));
                    break;
                case LOG_FULL_INVENTORY:
                    server_manager.send_to(client_id,
                                           EventFactory::chat_message(
                                               "El inventario está lleno!"));
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
    while (running) {
        auto start = std::chrono::steady_clock::now();
        try {
            if (forced_update || ++counter % ENTITY_UPDATE_INTERVAL == 0) {
                forced_update = true;
                counter = 0;
            }
            nlohmann::json map_data = map.get_update_data(forced_update);
            forced_update = false;
            if (map_data.contains("entities")) {
                handler.push_event(
                    EventFactory::update_entities(map_data["entities"]));
            }
            if (map_data.contains("items")) {
                handler.push_event(
                    EventFactory::update_items(map_data["items"]));
            }
            handler.push_event(EventFactory::update_map(map_data["positions"]));
            send_update_logs();

        } catch (const std::exception& e) {
            std::cerr << "Observer: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Observer: Unknown exception" << std::endl;
        }
        auto dif =
            OBSERVER_INTERVAL - (std::chrono::steady_clock::now() - start);
        sleep(dif);
    }
    std::cerr << "Observer finished" << std::endl;
}

void ThObserver::stop() {
    running = false;
}

ThObserver::~ThObserver() {}
