#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "../include/socket_manager.h"
#include "../nlohmann/json.hpp"
#include "map.h"
#include "session.h"

typedef unsigned int MapId;

class ServerManager {
   private:
    std::unordered_map<int, SocketManager*> clients;
    std::unordered_map<MapId, Map> maps;
    std::unordered_map<MapId, Session> sessions;
    ThDispatcherHandler dispatcher;

    ServerManager();

   public:
    static ServerManager& get_instance() {
        static ServerManager instance;
        return instance;
    }

    // TODO
    // En esta funcion se debe hacer new_client.assign_handler(dispatcher)
    void add_client(SocketManager* new_client);

    // TODO
    // Se crea la entidad player con la informaciónd del json y envía al jugador
    // el mensaje de inicialización
    void add_player(MapId map_id, int client_id, nlohmann::json player_info);

    SocketManager* get_client(int id);

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
