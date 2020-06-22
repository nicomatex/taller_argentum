#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../include/socket_exception.h"
#include "../nlohmann/json.hpp"
#include "event_factory.h"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : char_manager("../characters.dat", "../characters.json"),
      map_manager("assets/maps/forest1.json"),
      accepter(Socket("27016", 10)),
      game_loop(map_manager) {

    if (!char_manager.character_exists("nicolitox")) {
        character_t character_nico;
        character_nico = char_manager.create_character("nicolitox", 0, position_t{18,15}, 1, 2);
        char_manager.add_character(character_nico); 
    }
    
    if (!char_manager.character_exists("xxtaielxx")) {
        character_t character_taiel;
        character_taiel = char_manager.create_character("xxtaielxx", 0, position_t{20,21}, 2, 2);
        char_manager.add_character(character_taiel);
    }
    
    if (!char_manager.character_exists("fran")) {
        character_t character_fran;
        character_fran = char_manager.create_character("fran", 0, position_t{13,10}, 2, 1);
        char_manager.add_character(character_fran);
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
    clients.emplace(client_id, new_client);
    clients_status[client_id] = STATUS_CONNECTING;
}

void ServerManager::add_player(MapId map_id, ClientId client_id,
                               nlohmann::json player_data) {
    MapMonitor& map_monitor = map_manager[map_id];
    // Añadimos el jugador al mapa
    player_data["player_id"] = map_monitor.add_player(client_id, player_data);
    client_to_map[client_id] = map_id;

    // Enviamos la información de inicialización del mapa y del jugador
    nlohmann::json map_data = map_monitor.get_map_data();
    clients_status[client_id] = STATUS_CONNECTED;
    send_to(client_id, EventFactory::initialize_map(map_data, player_data));

    // Lo agregamos a la session correspondiente
    sessions.at(map_id).add_client(client_id);
}

void ServerManager::rm_client(ClientId client_id) {
    SocketManager* client = clients.at(client_id);
    clients.erase(client_id);
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

// void ServerManager::move_player(MapId to, ClientId client_id) {
//     nlohmann::json player_info = rm_player(client_id);
//     // Hacer algo con player_info
//     add_player(to, client_id, player_info);
// }

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    try {
        if (clients_status[client_id] == STATUS_CONNECTED)
            clients[client_id]->send(ev);
    } catch (const ConnectionClosedSocketException& e) {
        clients_status[client_id] = STATUS_DROPPING;
        dispatcher.push_event(EventFactory::drop_client(client_id));
    }
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

CharacterManager& ServerManager::get_character_manager() {
    return char_manager;
}

ServerManager::~ServerManager() {}
