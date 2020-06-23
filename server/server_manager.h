#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "../include/socket_manager.h"
#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "character_manager.h"
#include "clients_monitor.h"
#include "game_loop.h"
#include "map_manager.h"
#include "map_monitor.h"
#include "player.h"
#include "session.h"
#include "th_client_accepter.h"

typedef enum client_status {
    STATUS_CONNECTING,
    STATUS_CONNECTED,
    STATUS_DROPPING,
    STATUS_DISCONNECTED
} client_status_t;

class ServerManager {
   private:
    CharacterManager char_manager;
    MapManager map_manager;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<ClientId, MapId> client_to_map;
    ClientsMonitor clients;
    std::unordered_map<ClientId, client_status_t> clients_status;
    GameLoop game_loop;
    ThDispatcher dispatcher;
    ThClientAccepter accepter;

    ServerManager();

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();

    void add_client(ClientId client_id, SocketManager* new_client);

    void add_player(MapId map_id, ClientId client_id,
                    nlohmann::json player_info);

    void rm_client(ClientId client_id);

    nlohmann::json rm_player(ClientId client_id);

    void send_to(ClientId client_id, const Event& ev);

    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

    Session& get_session(ClientId client_id);

    void finish();

    CharacterManager& get_character_manager();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
