#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../include/socket_exception.h"
#include "../nlohmann/json.hpp"
#include "event_factory.h"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : char_manager("database/characters.dat", "database/characters.json"),
      map_manager("assets/maps/forest1.json"),
      accepter(Socket("27016", 10)),
      game_loop(map_manager) {
    if (!char_manager.character_exists("nicomatex")) {
        nlohmann::json nico_info = {
            {"name", "nicomatex"}, {"map_id", 0},    {"pos", position_t{18, 5}},
            {"head_id", 1},        {"body_id", 2},   {"helmet_id", 1},
            {"armor_id", 1},       {"shield_id", 2}, {"weapon_id", 5}};
        char_manager.add_character(nico_info);
    }

    if (!char_manager.character_exists("tai")) {
        nlohmann::json taiel_info = {
            {"name", "tai"}, {"map_id", 0},    {"pos", position_t{20, 21}},
            {"head_id", 2},  {"body_id", 2},   {"helmet_id", 2},
            {"armor_id", 3}, {"shield_id", 2}, {"weapon_id", 6}};
        char_manager.add_character(taiel_info);
    }

    if (!char_manager.character_exists("fran")) {
        nlohmann::json fran_info = {
            {"name", "fran"}, {"map_id", 0},    {"pos", position_t{13, 20}},
            {"head_id", 2},   {"body_id", 1},   {"helmet_id", 1},
            {"armor_id", 2},  {"shield_id", 1}, {"weapon_id", 9}};
        char_manager.add_character(fran_info);
    }

    if (!char_manager.character_exists("eze")) {
        nlohmann::json eze_info = {
            {"name", "eze"}, {"map_id", 0},    {"pos", position_t{23, 20}},
            {"head_id", 2},  {"body_id", 1},   {"helmet_id", 2},
            {"armor_id", 1}, {"shield_id", 1}, {"weapon_id", 1}};
        char_manager.add_character(eze_info);
    }

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
    clients.add_client(client_id, new_client);
    clients_status[client_id] = STATUS_CONNECTING;
}

void ServerManager::add_player(ClientId client_id, nlohmann::json player_data) {
    std::cerr << player_data << std::endl;
    MapMonitor& map_monitor = map_manager[player_data["map_id"]];
    // Añadimos el jugador al mapa
    player_data["player_id"] = map_monitor.add_player(client_id, player_data);
    client_to_map[client_id] = player_data["map_id"];

    // Enviamos la información de inicialización del mapa y del jugador
    nlohmann::json map_data = map_monitor.get_map_data();
    clients_status[client_id] = STATUS_CONNECTED;
    send_to(client_id, EventFactory::initialize_map(map_data, player_data));

    // Lo agregamos a la session correspondiente
    sessions.at(player_data["map_id"]).add_client(client_id);
}

void ServerManager::rm_client(ClientId client_id) {
    SocketManager* client = clients.rm_client(client_id);
    client->stop(true);
    client->join();
    clients_status[client_id] = STATUS_DISCONNECTED;
    delete client;
}

nlohmann::json ServerManager::rm_player(ClientId client_id) {
    // Eliminamos el jugador del mapa
    MapId map_id = client_to_map.at(client_id);
    client_to_map.erase(client_id);
    nlohmann::json player_data = map_manager[map_id].rm_player(client_id);
    player_data["map_id"] = map_id;

    // Eliminamos el jugador de la session
    sessions.at(map_id).rm_client(client_id);
    std::cerr << "ServerManager: removing player: " << player_data << std::endl;
    return player_data;
}

// void ServerManager::change_player_map(MapId to, ClientId client_id) {
//     nlohmann::json player_info = rm_player(client_id);
//     // Hacer algo con player_info
//     // Cambiar el id de session
//     add_player(to, client_id, player_info);
// }

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    try {
        if (clients_status[client_id] == STATUS_CONNECTED)
            clients.send_to(client_id, ev);
    } catch (const ConnectionClosedSocketException& e) {
        clients_status[client_id] = STATUS_DROPPING;
        dispatcher.push_event(EventFactory::drop_client(client_id));
    }
}

void ServerManager::finish() {
    accepter.stop();
    accepter.join();
    std::cerr << "Accepter: joined\n";
    for (auto& it : clients_status) {
        it.second = STATUS_DROPPING;
        dispatcher.push_event(EventFactory::drop_client(it.first));
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

CharacterManager& ServerManager::get_character_manager() {
    return char_manager;
}

ServerManager::~ServerManager() {}
