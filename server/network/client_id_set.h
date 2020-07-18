#ifndef CLIENTS_IDS_SET_H
#define CLIENTS_IDS_SET_H

#include <mutex>
#include <unordered_map>

#include "../../include/event.h"
#include "../../include/types.h"

class ClientToEntityMap {
   private:
    std::mutex m;
    std::unordered_map<ClientId, EntityId> client_to_entity;

   public:
    ClientToEntityMap();

    void add_client(ClientId client_id, EntityId entity_id);

    void rm_client(ClientId client_id);

    bool count(ClientId client_id);

    EntityId at(ClientId client_id);

    void send_to(ClientId client_id, const Event& ev);

    void broadcast(Event& ev);

    ~ClientToEntityMap();
};

#endif  // CLIENTS_IDS_SET_H
