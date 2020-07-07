#include "server_manager.h"

#include <fstream>
#include <vector>

#include "../include/event.h"
#include "../include/nlohmann/json.hpp"
#include "attribute_manager.h"
#include "events/event_factory.h"
#include "race_graphics_manager.h"

// Temp
#include <iostream>

ServerManager::ServerManager()
    : character_manager("database/characters.dat", "database/characters.json"),
      map_manager("ind/maps_index.json"),
      accepter(Socket("27016", 10)),
      game_loop(map_manager),
      item_factory("ind/items.json"),
      mob_factory("ind/mobs.json") {
    AttributeManager::init("ind/stats.json", "ind/races.json",
                           "ind/classes.json");
    RaceGraphicsManager::init("ind/races_graphics.json");
    if (!character_manager.character_exists("nicomatex")) {
        nlohmann::json nico_info = {{"name", "nicomatex"},
                                    {"map_id", 0},
                                    {"pos", position_t{13, 21}},
                                    {"head_id", 1},
                                    {"body_id", 2},
                                    {"helmet_id", 1},
                                    {"armor_id", 100},
                                    {"shield_id", 200},
                                    {"weapon_id", 303},
                                    {"curr_hp", 57},
                                    {"curr_mp", 50},
                                    {"class_type", MAGE},
                                    {"race_type", HUMAN},
                                    {"curr_level", 8},
                                    {"curr_exp", 34000},
                                    {"alive", true}};

        nico_info["inventory"] =
            R"({"items_ids":[401,300,200,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[50,1,1,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":10})"_json;
        character_manager.add_character(nico_info);
    }

    if (!character_manager.character_exists("tai")) {
        nlohmann::json taiel_info = {{"name", "tai"},
                                     {"map_id", 0},
                                     {"pos", position_t{20, 21}},
                                     {"head_id", 2},
                                     {"body_id", 2},
                                     {"helmet_id", 2},
                                     {"armor_id", 101},
                                     {"shield_id", 201},
                                     {"weapon_id", 302},
                                     {"curr_hp", 70},
                                     {"curr_mp", 30},
                                     {"class_type", WARRIOR},
                                     {"race_type", DWARF},
                                     {"curr_level", 16},
                                     {"curr_exp", 131000},
                                     {"alive", true}};
        taiel_info["inventory"] = R"({"items_ids":[401,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[1200,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;
        character_manager.add_character(taiel_info);
    }

    if (!character_manager.character_exists("fran")) {
        nlohmann::json fran_info = {
            {"name", "fran"},   {"map_id", 0},      {"pos", position_t{13, 20}},
            {"head_id", 2},     {"body_id", 1},     {"helmet_id", 3},
            {"armor_id", 102},  {"shield_id", 201}, {"weapon_id", 301},
            {"curr_hp", 100},   {"curr_mp", 70},    {"class_type", PALADIN},
            {"race_type", ELF}, {"curr_level", 1},  {"curr_exp", 300},
            {"alive", true}};
        fran_info["inventory"] = R"({"items_ids":[401,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[1200,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":140})"_json;
        character_manager.add_character(fran_info);
    }

    if (!character_manager.character_exists("eze")) {
        nlohmann::json eze_info = {{"name", "eze"},
                                   {"map_id", 0},
                                   {"pos", position_t{23, 20}},
                                   {"head_id", 2},
                                   {"body_id", 1},
                                   {"helmet_id", 1},
                                   {"armor_id", 100},
                                   {"shield_id", 200},
                                   {"weapon_id", 300},
                                   {"curr_hp", 10},
                                   {"curr_mp", 10},
                                   {"class_type", PRIEST},
                                   {"race_type", GNOME},
                                   {"curr_level", 1},
                                   {"curr_exp", 200},
                                   {"alive", true}};
        eze_info["inventory"] = R"({"items_ids":[401,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[1200,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":120})"_json;
        character_manager.add_character(eze_info);
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
    client->join();
    rm_name(client_id);
    delete client;
}

void ServerManager::drop_client(ClientId client_id) {
    clients.drop(client_id);
}

void ServerManager::add_name(ClientId client_id, const std::string& name) {
    if (clients_names.right.count(name))
        throw DuplicatedPlayerException(name);
    clients_names.insert({client_id, name});
}
void ServerManager::rm_name(ClientId client_id) {
    if (!clients_names.left.count(client_id))
        // Este caso sirve si un jugador nunca mandó el mensaje de
        // inicialización
        return;
    std::string name = clients_names.left.at(client_id);
    clients_names.left.erase(client_id);
    clients_names.right.erase(name);
}

void ServerManager::add_player(ClientId client_id, nlohmann::json player_data,
                               bool send_map_data) {
    m.lock();
    // add_name(client_id, player_data["name"]);
    MapId map_id = player_data["map_id"];
    MapMonitor& map_monitor = map_manager[map_id];
    // Añadimos el jugador al mapa
    player_data = map_monitor.add_player(client_id, player_data);
    client_to_map[client_id] = map_id;
    player_data["pos"] = map_monitor.get_position(client_id);

    std::cerr << "ServerManager: adding player: " << player_data["name"]
              << " in map " << map_id << " at " << player_data["pos"]["x"]
              << "," << player_data["pos"]["y"] << std::endl;

    // Enviamos la información de inicialización del mapa y del jugador
    nlohmann::json map_data = map_monitor.get_map_data();
    nlohmann::json map_updates = map_monitor.get_update_data(true);
    send_to(client_id, EventFactory::initialize_map(map_data, player_data));
    send_to(client_id, EventFactory::update_entities(map_updates["entities"]));
    send_to(client_id, EventFactory::update_items(map_updates["items"]));

    std::cerr << "ServerManager: sent initialize msg to: " << client_id
              << std::endl;

    // Lo agregamos a la session correspondiente
    sessions.at(map_id).add_client(client_id);
    m.unlock();
}

nlohmann::json ServerManager::rm_player(ClientId client_id) {
    m.lock();
    // Eliminamos el jugador del mapa
    MapId map_id = client_to_map.at(client_id);
    client_to_map.erase(client_id);
    nlohmann::json player_data = map_manager[map_id].rm_player(client_id);
    player_data["map_id"] = map_id;

    std::cerr << "ServerManager: removing player: " << player_data["name"]
              << " in map " << player_data["map_id"] << " at "
              << player_data["pos"]["x"] << "," << player_data["pos"]["y"]
              << std::endl;

    // Eliminamos el jugador de la session
    sessions.at(map_id).rm_client(client_id);
    m.unlock();
    return player_data;
}

void ServerManager::send_to(ClientId client_id, const Event& ev) {
    clients.send_to(client_id, ev);
}

void ServerManager::finish() {
    accepter.stop();
    accepter.join();
    std::cerr << "Accepter: joined\n";
    clients.drop_all();
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

std::string ServerManager::get_name_by_client(ClientId client_id) {
    if (!clients_names.left.count(client_id))
        throw ClientDisconnectedException(client_id);
    return clients_names.left.at(client_id);
}

ClientId ServerManager::get_client_by_name(const std::string& name) {
    if (!clients_names.right.count(name))
        throw ClientDisconnectedException(name);
    return clients_names.right.at(name);
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
    return character_manager;
}

ServerManager::~ServerManager() {}
