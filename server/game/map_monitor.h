#ifndef __MAP_MONITOR_H
#define __MAP_MONITOR_H

#include <mutex>
#include <queue>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "actions/action.h"
#include "map.h"
#include "map_log_factory.h"
#include "map_transitions.h"

class MapMonitor {
   private:
    std::recursive_mutex m;
    Map map;

   public:
    MapMonitor(MapId map_id, const std::string& map_name, bool is_safe,
               const nlohmann::json& map_description,
               const nlohmann::json& map_mobs,
               const nlohmann::json& map_transitions);
    ~MapMonitor();

    MapMonitor(const MapMonitor& other) = delete;

    const std::string& get_name();

    /**/
    nlohmann::json add_player(nlohmann::json player_info);

    nlohmann::json rm_player(EntityId entity_id);

    position_t get_position(EntityId entity_id);

    bool entity_exists(EntityId entity_id);

    std::queue<map_change_t> get_transitions();

    /* Actualiza el estado del mapa. */
    void update(uint64_t delta_t);

    /* Ejecuta sobre la entidad asociada al client_id la accion. */
    void push_action(EntityId entity_id, Action* action);

    std::vector<map_log_t> get_update_logs();

    nlohmann::json get_update_data(bool update_entities);

    nlohmann::json get_map_data();
};

#endif  // MAP_MONITOR_H