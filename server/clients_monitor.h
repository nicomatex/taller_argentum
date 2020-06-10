#ifndef CLIENTS_MONITOR_H
#define CLIENTS_MONITOR_H

#include <mutex>
#include <unordered_map>

#include "../include/command.h"
#include "../include/socket_manager.h"

#define INVALID_ID -1

class ClientsMonitor {
   private:
    std::mutex mutex;
    std::unordered_map<int, SocketManager*> clients;

   public:
    ClientsMonitor();

    void add_client(SocketManager* new_client);

    SocketManager* rm_client(int id);

    void send_to(size_t id, const Command& ev);

    void broadcast(Command& ev);

    void join_finished(bool wait);

    ~ClientsMonitor();
};

#endif  // CLIENTS_MONITOR_H
