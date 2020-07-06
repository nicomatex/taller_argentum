#include "map_log_factory.h"

map_log_t MapLogFactory::inventory_change(const std::string& name,
                                          nlohmann::json inventory_data) {
    return {LOG_INVENTORY, name, inventory_data};
}

map_log_t MapLogFactory::deal_damage(const std::string& name,
                                     nlohmann::json damage_info) {
    return {LOG_DEAL_DAMAGE, name, damage_info};
}

map_log_t MapLogFactory::receive_damage(const std::string& name,
                                        nlohmann::json damage_info) {
    return {LOG_RECV_DAMAGE, name, damage_info};
}
