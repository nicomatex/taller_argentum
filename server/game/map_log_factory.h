#ifndef MAP_LOG_FACTORY_H
#define MAP_LOG_FACTORY_H

#include "../../include/nlohmann/json.hpp"
#include "map.h"

class MapLogFactory {
   public:
    static map_log_t inventory_change(const std::string& name,
                                      nlohmann::json inventory);

    static map_log_t deal_damage(const std::string& name,
                                 nlohmann::json damage_info);

    static map_log_t receive_damage(const std::string& name,
                                    nlohmann::json damage_info);
};

#endif  // MAP_LOG_FACTORY_H
