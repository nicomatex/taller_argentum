#ifndef __MAP_MONITOR_H
#define __MAP_MONITOR_H

#include <mutex>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "action.h"
#include "map.h"

// Clave: id de cliente, valor: id de entidad del jugador.
typedef std::unordered_map<ClientId, EntityId> ClientMap;

class MapMonitor {
   private:
    Map map;
    std::mutex m;
    ClientMap client_map;

   public:
    MapMonitor(nlohmann::json map_description);
    ~MapMonitor();
    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    EntityId add_player(ClientId client_id, nlohmann::json player_info);

    nlohmann::json rm_player(ClientId client_id);

    /* Actualiza el estado del mapa. */
    void update(uint64_t delta_t);

    /* Ejecuta sobre la entidad asociada al client_id la accion. */
    void with_player(ClientId client_id, const Action& action);

    nlohmann::json get_update_data(bool& update_entities);

    nlohmann::json get_map_data();
};

#endif  // MAP_MONITOR_H