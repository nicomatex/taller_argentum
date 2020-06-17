#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../nlohmann/json.hpp"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : map_manager("assets/maps/forest1.json"),
      accepter(Socket("8080", 10)),
      game_loop(map_manager) {
    std::vector<MapId> v = map_manager.get_ids();
    for (auto& it : v) {
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
                               nlohmann::json player_info) {
    // Añadimos el jugador al mapa
    player_info["player_id"] =
        map_manager[map_id].add_player(client_id, player_info);
    client_to_map[client_id] = map_id;

    // Enviamos la información del mapa
    nlohmann::json map_data = map_manager[map_id].get_map_data();
    map_data["ev_id"] = 1;
    clients[client_id]->send(Event(map_data));

    // Enviamos la información del jugador
    player_info["ev_id"] = 0;
    clients[client_id]->send(Event(player_info));

    // Lo agregamos a la session correspondiente
    sessions.at(map_id).add_client(client_id);
}

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    // if (!clients.count(client_id))
    //     throw ClientDisconnectedException();
    clients[client_id]->send(ev);
}

Player& ServerManager::get_player(ClientId client_id) {
    return (map_manager[client_to_map[client_id]]).get_player(client_id);
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

ServerManager::~ServerManager() {}
