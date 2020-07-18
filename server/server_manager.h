#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <mutex>
#include <string>

#include "../include/network/socket_manager.h"
#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "character_manager.h"
#include "clients_names_monitor.h"
#include "game/game_manager.h"
#include "map_changer.h"
#include "network/clients_monitor.h"
#include "network/th_client_accepter.h"
#include "server_exceptions.h"
#include "session.h"
#include "th_dispatcher.h"

class ServerManager {
   private:
    GameManager game_manager;

    std::recursive_mutex m;
    ThClientAccepter accepter;
    CharacterManager character_manager;
    MapChanger map_changer;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<ClientId, MapId> client_to_map;
    ClientsNamesMonitor clients_names;
    ClientsMonitor clients;
    ThDispatcher dispatcher;

    ServerManager();

    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();
    void dispatch(const Event& ev);

    void add_client(ClientId client_id, SocketManager* new_client);
    void rm_client(ClientId client_id);
    void drop_client(ClientId client_id);

    void add_player(ClientId client_id, nlohmann::json player_info);
    nlohmann::json rm_player(ClientId client_id);
    nlohmann::json change_player_map(ClientId client_id,
                                     position_t new_position, MapId new_map);

    void send_to(ClientId client_id, const Event& ev);

    std::string get_name_by_client(ClientId client_id);
    ClientId get_client_by_name(const std::string& name);

    Session& get_session(ClientId client_id);

    void finish();

    CharacterManager& get_character_manager();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
