#ifndef CLIENTS_MONITOR_H
#define CLIENTS_MONITOR_H

#include <mutex>
#include <unordered_map>

#include "../include/event.h"
#include "../include/socket_manager.h"

#define INVALID_ID -1

class ClientsMonitor {
   private:
    std::mutex mutex;
    std::vector<int> clients;

   public:
    ClientsMonitor();

    void add_client(SocketManager* new_client);

    SocketManager* rm_client(int id);

    void send_to(size_t id, const Event& ev);

    void broadcast(Event& ev);

    void join_finished(bool wait);

    ~ClientsMonitor();
};

#endif  // CLIENTS_MONITOR_H
