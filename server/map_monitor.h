#ifndef __MAP_MONITOR_H
#define __MAP_MONITOR_H
#include <mutex>
#include "../include/types.h"
#include "map.h"
#include "action.h"
#include "../nlohmann/json.hpp"

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
    
    /* Actualiza el estado del mapa. */
    void update(uint64_t delta_t);

    /* Ejecuta sobre la entidad asociada al client_id la accion. */
    void with_player(ClientId client_id,const Action& action);

    nlohmann::json get_position_data();

    nlohmann::json get_entity_data();

    nlohmann::json get_map_data();
};

#endif  // MAP_MONITOR_H