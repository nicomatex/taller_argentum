#ifndef CLIENTS_IDS_SET_H
#define CLIENTS_IDS_SET_H

#include <mutex>
#include <unordered_set>

#include "../include/event.h"

#define INVALID_ID -1

class ClientIdSet {
   private:
    std::mutex mutex;
    std::unordered_set<int> clients;

   public:
    ClientIdSet();

    void add_client(int client_id);

    void rm_client(int id);

    void send_to(int id, const Event& ev);

    void broadcast(Event& ev);

    ~ClientIdSet();
};

#endif  // CLIENTS_IDS_SET_H
