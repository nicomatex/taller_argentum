#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../nlohmann/json.hpp"
#include "event_factory.h"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : map_manager("assets/maps/forest1.json"),
      accepter(Socket("8080", 10)),
      game_loop(map_manager) {
    std::vector<MapId> v = map_manager.get_ids();
    for (auto& it : v) {
        std::cerr << "ServerManager: creating session for map id: " << it
                  << std::endl;
        sessions.emplace(it, map_manager[it]);
        sessions.at(it).start();
    }
    game_loop.start();
    dispatcher.start();
    accepter.start();
}

ServerManager& ServerManager::get_instance() {
    static ServerManager instance;
    return instance;
}

ThDispatcher& ServerManager::get_dispatcher() {
    return dispatcher;
}

void ServerManager::add_client(ClientId client_id, SocketManager* new_client) {
    clients.emplace(client_id, new_client);
}

void ServerManager::add_player(MapId map_id, ClientId client_id,
                               nlohmann::json player_data) {
    MapMonitor& map_monitor(map_manager[map_id]);
    // Añadimos el jugador al mapa
    player_data["player_id"] = map_monitor.add_player(client_id, player_data);
    client_to_map[client_id] = map_id;

    // Enviamos la información de inicialización del mapa y del jugador
    nlohmann::json map_data = map_monitor.get_map_data();
    clients[client_id]->send(
        EventFactory::initialize_map(map_data, player_data));
    bool update = true;
    clients[client_id]->send(
        EventFactory::update_entities(map_monitor.get_update_data(update)));

    // Lo agregamos a la session correspondiente
    sessions.at(map_id).add_client(client_id);
}

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    // if (!clients.count(client_id))
    //     throw ClientDisconnectedException();
    clients[client_id]->send(ev);
}

void ServerManager::finish() {
    accepter.stop();
    accepter.join();
    std::cerr << "Accepter: joined\n";
    for (auto& it : clients) {
        SocketManager* client = it.second;
        client->send(Event(nlohmann::json({"ev_id", -1})));
    }
    dispatcher.stop();
    dispatcher.join();
    std::cerr << "Dispatcher: joined\n";
    for (auto& it : sessions) {
        it.second.stop();
        it.second.join();
    }
    std::cerr << "Sessions: joined all\n";
    game_loop.stop();
    game_loop.join();
    std::cerr << "GameLoop: joined\n";
}

MapMonitor& ServerManager::get_map_by_client(ClientId client_id) {
    return get_map(client_to_map.at(client_id));
}

MapMonitor& ServerManager::get_map(MapId map_id) {
    return map_manager[map_id];
}

Session& ServerManager::get_session(ClientId client_id) {
    return sessions.at(client_to_map.at(client_id));
}

ServerManager::~ServerManager() {}
