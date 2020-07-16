#ifndef MAP_LOG_FACTORY_H
#define MAP_LOG_FACTORY_H

#include "../../include/nlohmann/json.hpp"
#include "position.h"

typedef enum log_type {
    LOG_INVENTORY,
    LOG_INVENTORY_FULL,
    LOG_DEAL_DAMAGE,
    LOG_RECV_DAMAGE,
    // LOG_RECV_HEAL,
    LOG_SPECIAL_ABILITY,
    LOG_MESSAGE,
    LOG_RESUSCITATE
} log_type_t;

typedef struct map_log {
    log_type_t type;
    std::string player_name;
    nlohmann::json info;
} map_log_t;

class MapLogFactory {
   public:
    static map_log_t inventory_change(const std::string& player_name,
                                      nlohmann::json inventory);

    static map_log_t inventory_full(const std::string& player_name);

    static map_log_t deal_damage(const std::string& player_name,
                                 nlohmann::json damage_info);

    static map_log_t receive_damage(const std::string& player_name,
                                    nlohmann::json damage_info);
    static map_log_t message(const std::string& player_name,
                             nlohmann::json message_info);

    static map_log_t special_ability(const std::string& player_name,
                                     uint32_t ability_id, position_t source,
                                     position_t dest);

    static map_log_t resuscitate(const std::string& player_name,
                                 nlohmann::json message_info);                                   
};

#endif  // MAP_LOG_FACTORY_H
