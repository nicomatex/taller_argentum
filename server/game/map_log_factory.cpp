#include "map_log_factory.h"

map_log_t MapLogFactory::inventory_change(const std::string& player_name,
                                          nlohmann::json inventory_data) {
    return {LOG_INVENTORY, player_name, inventory_data};
}

map_log_t MapLogFactory::inventory_full(const std::string& player_name) {
    return {LOG_INVENTORY_FULL, player_name};
}

map_log_t MapLogFactory::deal_damage(const std::string& player_name,
                                     nlohmann::json damage_info) {
    return {LOG_DEAL_DAMAGE, player_name, damage_info};
}

map_log_t MapLogFactory::receive_damage(const std::string& player_name,
                                        nlohmann::json damage_info) {
    return {LOG_RECV_DAMAGE, player_name, damage_info};
}

map_log_t MapLogFactory::message(const std::string& player_name,
                                 nlohmann::json message_info) {
    return {LOG_MESSAGE, player_name, message_info};
}

map_log_t MapLogFactory::special_ability(const std::string& player_name,
                                         uint32_t ability_id, position_t source,
                                         position_t dest) {
    return {
        LOG_SPECIAL_ABILITY, player_name,
        nlohmann::json{
            {"ability_id", ability_id}, {"source", source}, {"dest", dest}}};
}
