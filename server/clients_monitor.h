#ifndef CLIENTS_MONITOR_H
#define CLIENTS_MONITOR_H

#include <mutex>
#include <unordered_map>

#include "../include/event.h"
#include "../include/socket_exception.h"
#include "../include/socket_manager.h"
#include "../include/types.h"

class ClientsMonitor {
   private:
    std::mutex m;
    std::unordered_map<ClientId, SocketManager*> clients;

   public:
    ClientsMonitor();
    ~ClientsMonitor();

    void add_client(ClientId client_id, SocketManager* client);

    SocketManager* rm_client(ClientId client_id);

    void send_to(ClientId, Event ev);
};

#endif  // CLIENTS_MONITOR_H
