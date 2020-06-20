#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "../include/socket_manager.h"
#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "game_loop.h"
#include "map_manager.h"
#include "map_monitor.h"
#include "player.h"
#include "session.h"
#include "th_client_accepter.h"

class ServerManager {
   private:
    MapManager map_manager;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<ClientId, MapId> client_to_map;
    std::unordered_map<ClientId, SocketManager*> clients;
    GameLoop game_loop;
    ThDispatcher dispatcher;
    ThClientAccepter accepter;

    ServerManager();

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();

    void add_client(ClientId client_id, SocketManager* new_client);

    // TODO
    // Se crea la entidad player con la informaciónd del json y envía al jugador
    // el mensaje de inicialización
    void add_player(MapId map_id, ClientId client_id,
                    nlohmann::json player_info);

    void send_to(ClientId client_id, const Event& ev);

    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

    Session& get_session(ClientId client_id);

    void finish();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
