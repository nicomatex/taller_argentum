#ifndef SESSION_H
#define SESSION_H

#include <mutex>

#include "../include/event.h"
#include "../include/types.h"
#include "map_monitor.h"
#include "network/client_id_set.h"
#include "network/th_broadcaster.h"
#include "th_observer.h"

// Clave: id de cliente, valor: id de entidad del jugador.
typedef std::unordered_map<ClientId, EntityId> ClientMap;

class Session {
   private:
    MapMonitor& map;
    ClientIdSet clients;
    std::mutex m;
    ClientMap client_map;
    ThBroadcaster broadcaster;
    ThObserver observer;

   public:
    Session(MapMonitor& map);

    void start();

    void finish();

    void add_client(ClientId new_client, EntityId entity_id);

    EntityId rm_client(ClientId client_id);

    void push_action(ClientId client_id, Action* action);

    MapMonitor& get_map();

    void broadcast(const Event& ev);

    ~Session();
};

#endif  // SESSION_H
