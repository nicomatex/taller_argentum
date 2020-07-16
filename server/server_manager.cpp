#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../include/event.h"
#include "../include/nlohmann/json.hpp"
#include "attribute_manager.h"
#include "configuration_manager.h"
#include "events/event_factory.h"
#include "game/bank.h"
#include "race_graphics_manager.h"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : accepter(Socket("27016", 10)),
      character_manager("database/characters.dat", "database/characters.json"),
      map_manager("ind/maps_index.json"),
      map_changer(map_manager),
      game_loop(map_manager),
      item_factory("ind/items.json"),
      mob_factory("ind/mobs.json") {
    AttributeManager::init("ind/stats.json", "ind/races.json",
                           "ind/classes.json");
    RaceGraphicsManager::init("ind/races_graphics.json");
    ConfigurationManager::init("ind/config.json");
    std::vector<MapId> v = map_manager.get_ids();
    for (auto& it : v) {
        std::cerr << "ServerManager: creating session for map id: " << it
                  << std::endl;
        sessions.emplace(it, map_manager[it]);
        sessions.at(it).start();
    }
    map_changer.start();
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

void ServerManager::dispatch(const Event& ev) {
    dispatcher.push_event(ev);
}

ItemFactory& ServerManager::get_item_factory() {
    return item_factory;
}
MobFactory& ServerManager::get_mob_factory() {
    return mob_factory;
}

void ServerManager::add_client(ClientId client_id, SocketManager* new_client) {
    clients.add_client(client_id, new_client);
}

void ServerManager::rm_client(ClientId client_id) {
    SocketManager* client = clients.rm_client(client_id);
    client->stop(true);
    std::cerr << "ServerManager: stopped client: " << client_id << std::endl;
    client->join();
    std::cerr << "ServerManager: joined client: " << client_id << std::endl;
    rm_name(client_id);
    delete client;
}

void ServerManager::drop_client(ClientId client_id) {
    clients.drop(client_id);
}

void ServerManager::add_name(ClientId client_id, const std::string& name) {
    clients_names.add_name(client_id, name);
}
void ServerManager::rm_name(ClientId client_id) {
    clients_names.rm_name(client_id);
}

void ServerManager::add_player(ClientId client_id, nlohmann::json player_data) {
    std::unique_lock<std::recursive_mutex> l(m);
    // add_name(client_id, player_data["name"]);
    Bank::get_instance().add_account(player_data["name"], player_data["vault"]);
    MapId map_id = player_data["map_id"];

    std::cerr << "ServerManager: adding player: " << player_data["name"]
              << " in map " << map_id << " at " << player_data["pos"]["x"]
              << "," << player_data["pos"]["y"] << std::endl;

    MapMonitor& map_monitor = get_map(map_id);
    // Añadimos el jugador al mapa
    player_data = map_monitor.add_player(player_data);
    client_to_map[client_id] = map_id;
    player_data["pos"] = map_monitor.get_position(player_data["entity_id"]);

    // Notificación de conexión a nuevo mapa
    send_to(client_id, EventFactory::notify_new_map());

    // Enviamos la información de inicialización del mapa y del jugador
    nlohmann::json map_data = map_monitor.get_map_data();
    nlohmann::json map_updates = map_monitor.get_update_data(true);
    send_to(client_id, EventFactory::initialize_map(map_data, player_data));
    send_to(client_id, EventFactory::update_entities(map_updates["entities"]));
    send_to(client_id, EventFactory::update_items(map_updates["items"]));

    // Lo agregamos a la session correspondiente
    sessions.at(map_id).add_client(client_id, player_data["entity_id"]);

    std::cerr << "ServerManager: sent initialize msg to: " << client_id
              << std::endl;
}

nlohmann::json ServerManager::rm_player(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    // Eliminamos el jugador del mapa
    MapId map_id = client_to_map.at(client_id);
    client_to_map.erase(client_id);
    EntityId player_id = sessions.at(map_id).rm_client(client_id);
    nlohmann::json player_data = get_map(map_id).rm_player(player_id);
    player_data["map_id"] = map_id;
    player_data["vault"] =
        Bank::get_instance().remove_account(player_data["name"]);

    // std::cerr << "ServerManager: removing player: " << player_data["name"]
    //           << " in map " << player_data["map_id"] << " at "
    //           << player_data["pos"]["x"] << "," << player_data["pos"]["y"]
    //           << std::endl;
    return player_data;
}

nlohmann::json ServerManager::change_player_map(ClientId client_id,
                                                position_t new_pos,
                                                MapId new_map) {
    std::unique_lock<std::recursive_mutex> l(m);
    nlohmann::json player_data = rm_player(client_id);
    player_data["map_id"] = new_map;
    player_data["pos"] = new_pos;
    send_to(client_id, EventFactory::notify_new_map());
    add_player(client_id, player_data);
    return player_data;
}

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    clients.send_to(client_id, ev);
}

void ServerManager::finish() {
    std::unique_lock<std::recursive_mutex> l(m);
    accepter.stop();
    clients.drop_all();
    dispatcher.stop();
    map_manager.close();
    game_loop.stop();
    l.unlock();
    for (auto& it : sessions) {
        it.second.finish();
    }
    std::cerr << "Sessions: finished all\n";
    accepter.join();
    std::cerr << "Accepter: joined\n";
    dispatcher.join();
    std::cerr << "Dispatcher: joined\n";
    game_loop.join();
    std::cerr << "GameLoop: joined\n";
    map_changer.join();
    std::cerr << "MapChanger: joined\n";
}

std::string ServerManager::get_name_by_client(ClientId client_id) {
    return clients_names.get_name(client_id);
}

ClientId ServerManager::get_client_by_name(const std::string& name) {
    return clients_names.get_client(name);
}

MapMonitor& ServerManager::get_map_by_client(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    return get_map(client_to_map.at(client_id));
}

MapMonitor& ServerManager::get_map(MapId map_id) {
    return sessions.at(map_id).get_map();
}

Session& ServerManager::get_session(ClientId client_id) {
    std::unique_lock<std::recursive_mutex> l(m);
    return sessions.at(client_to_map.at(client_id));
}

CharacterManager& ServerManager::get_character_manager() {
    return character_manager;
}

ServerManager::~ServerManager() {}
