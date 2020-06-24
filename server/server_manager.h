#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <boost/bimap.hpp>
#include <stdexcept>
#include <string>

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

class ClientDisconnectedException : public std::exception {
   private:
    char err_msg[100];

   public:
    ClientDisconnectedException(ClientId client_id) {
        std::string str =
            "The client: " + std::to_string(client_id) + " has disconnected.";
        strncpy(err_msg, str.c_str(), 100);
        err_msg[99] = '\0';
    }
    ClientDisconnectedException(std::string name) {
        std::string str = "The client: " + name + " has disconnected.";
        strncpy(err_msg, str.c_str(), 100);
        err_msg[99] = '\0';
    }
    ~ClientDisconnectedException() {}

    const char* what() const noexcept override {
        return err_msg;
    }
};

class ServerManager {
   private:
    CharacterManager char_manager;
    MapManager map_manager;
    std::unordered_map<MapId, Session> sessions;
    std::unordered_map<ClientId, MapId> client_to_map;
    boost::bimap<ClientId, std::string> clients_names;
    ClientsMonitor clients;
    GameLoop game_loop;
    ThDispatcher dispatcher;
    ThClientAccepter accepter;

    ServerManager();

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();

    void add_client(ClientId client_id, SocketManager* new_client);

    void add_player(ClientId client_id, nlohmann::json player_info);

    void drop_client(ClientId client_id);

    void rm_client(ClientId client_id);

    nlohmann::json rm_player(ClientId client_id);

    void send_to(ClientId client_id, const Event& ev);

    std::string get_name_by_client(ClientId client_id);
    ClientId get_client_by_name(const std::string& name);

    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

    Session& get_session(ClientId client_id);

    void finish();

    CharacterManager& get_character_manager();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
