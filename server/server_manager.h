#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "../include/socket_manager.h"
#include "../nlohmann/json.hpp"
#include "game_loop.h"
#include "map.h"
#include "map_manager.h"
#include "player.h"
#include "session.h"
#include "th_client_accepter.h"

class ServerManager {
   private:
    MapManager map_manager;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<int, MapId> client_to_map;
    std::unordered_map<int, SocketManager*> clients;
    GameLoop game_loop;
    ThDispatcher dispatcher;
    ThClientAccepter accepter;

    ServerManager();

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();

    void add_client(int client_id, SocketManager* new_client);

    // TODO
    // Se crea la entidad player con la informaciónd del json y envía al jugador
    // el mensaje de inicialización
    void add_player(MapId map_id, int client_id, nlohmann::json player_info);

    void send_to(int client_id, const Event& ev);

    Player& get_player(int client_id);

    void finish();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
