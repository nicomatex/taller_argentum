#ifndef __MAP_MONITOR_H
#define __MAP_MONITOR_H

#include <mutex>
#include <queue>

#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "game/actions/action.h"
#include "game/map.h"
#include "game/map_transitions.h"

// Clave: id de cliente, valor: id de entidad del jugador.
typedef std::unordered_map<ClientId, EntityId> ClientMap;

class MapMonitor {
   private:
    std::recursive_mutex m;
    Map map;
    ClientMap client_map;

   public:
    MapMonitor(nlohmann::json map_description);
    ~MapMonitor();
    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    nlohmann::json add_player(ClientId client_id, nlohmann::json player_info);

    nlohmann::json rm_player(ClientId client_id);

    position_t get_position(ClientId client_id);

    std::queue<map_change_t> get_transitions();

    /* Actualiza el estado del mapa. */
    void update(uint64_t delta_t);

    /* Ejecuta sobre la entidad asociada al client_id la accion. */
    void push_action(ClientId client_id, Action* action);

    std::vector<nlohmann::json> get_update_logs();

    bool dirty_entities() const;
    bool dirty_loot() const;
    nlohmann::json get_update_data(bool update_entities);

    nlohmann::json get_map_data();
};

#endif  // MAP_MONITOR_H