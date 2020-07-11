#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <mutex>
#include <string>

#include "../include/network/socket_manager.h"
#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "character_manager.h"
#include "clients_names_monitor.h"
#include "game/game_loop.h"
#include "game/items/item_factory.h"
#include "game/mob_factory.h"
#include "map_manager.h"
#include "map_monitor.h"
#include "network/clients_monitor.h"
#include "network/th_client_accepter.h"
#include "server_exceptions.h"
#include "session.h"

class ServerManager {
   private:
    CharacterManager character_manager;
    MapManager map_manager;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<ClientId, MapId> client_to_map;
    ClientsNamesMonitor clients_names;
    ClientsMonitor clients;
    GameLoop game_loop;
    ThDispatcher dispatcher;
    ThClientAccepter accepter;

    ItemFactory item_factory;
    MobFactory mob_factory;

    std::recursive_mutex m;

    ServerManager();

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();
    void dispatch(const Event& ev);

    ItemFactory& get_item_factory();
    MobFactory& get_mob_factory();

    void add_client(ClientId client_id, SocketManager* new_client);
    void rm_client(ClientId client_id);
    void drop_client(ClientId client_id);

    void add_player(ClientId client_id, nlohmann::json player_info,
                    bool send_map_data = true);
    nlohmann::json rm_player(ClientId client_id);

    void add_name(ClientId client_id, const std::string& name);
    void rm_name(ClientId client_id);

    void send_to(ClientId client_id, const Event& ev);

    std::string get_name_by_client(ClientId client_id);
    ClientId get_client_by_name(const std::string& name);

    MapId get_map_id(ClientId client_id);
    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

    Session& get_session(ClientId client_id);

    void finish();

    CharacterManager& get_character_manager();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
