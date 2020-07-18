#ifndef MAP_LOG_FACTORY_H
#define MAP_LOG_FACTORY_H

#include "../../include/nlohmann/json.hpp"
#include "position.h"

typedef enum log_type {
    LOG_INVENTORY,
    LOG_INVENTORY_FULL,
    LOG_DEAL_DAMAGE,
    LOG_RECV_DAMAGE,
    LOG_SPECIAL_ABILITY,
    LOG_MESSAGE,
    LOG_RESUSCITATE
} log_type_t;

typedef struct map_log {
    log_type_t type;
    std::string player_name;
    nlohmann::json info;
} map_log_t;

/**
 * @brief Constructor de logs del mapa.
 *
 * Cada log del mapa está construido por el tipo de log (`log_type_t`), por el
 * nombre del personaje al que se le debe enviar el log e información extra
 * particular de cada tipo dada por un `json`.
 *
 */
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
