#ifndef CLIENTS_IDS_SET_H
#define CLIENTS_IDS_SET_H

#include <mutex>
#include <unordered_set>

#include "../../include/event.h"
#include "../../include/types.h"

class ClientIdSet {
   private:
    std::mutex m;
    std::unordered_set<ClientId> clients;

   public:
    ClientIdSet();

    void add_client(ClientId id);

    void rm_client(ClientId id);

    void send_to(ClientId id, const Event& ev);

    void broadcast(Event& ev);

    ~ClientIdSet();
};

#endif  // CLIENTS_IDS_SET_H
