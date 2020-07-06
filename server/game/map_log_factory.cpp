#include "map_log_factory.h"

map_log_t MapLogFactory::inventory_change(const std::string& player_name,
                                          nlohmann::json inventory_data) {
    return {LOG_INVENTORY, player_name, inventory_data};
}

map_log_t MapLogFactory::inventory_full(const std::string& player_name) {
    return {LOG_FULL_INVENTORY, player_name};
}

map_log_t MapLogFactory::deal_damage(const std::string& player_name,
                                     nlohmann::json damage_info) {
    return {LOG_DEAL_DAMAGE, player_name, damage_info};
}

map_log_t MapLogFactory::receive_damage(const std::string& player_name,
                                        nlohmann::json damage_info) {
    return {LOG_RECV_DAMAGE, player_name, damage_info};
}
