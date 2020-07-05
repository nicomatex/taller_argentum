#ifndef __STATS_COMPONENT_H
#define __STATS_COMPONENT_H

#include <mutex>
#include <unordered_map>

#include "../../../include/nlohmann/json.hpp"
#include "../ECS/component.h"

typedef std::unordered_map<std::string, unsigned int> StatValues;

class StatsComponent : public Component {
   private:
    StatValues max_stat_values;
    StatValues current_stat_values;
    int level;

    std::recursive_mutex m;

   public:
    StatsComponent(int max_hp, int current_hp, int max_mp, int current_mp,
                   int max_xp, int current_xp, int level);

    unsigned int get_stat_current_value(const std::string &stat_name);
    unsigned int get_stat_max_value(const std::string &stat_name);

    void set_stat_current_value(const std::string &stat_name,
                                unsigned int new_value);
    void set_stat_max_value(const std::string &stat_name,
                            unsigned int new_value);
    int get_level();
    void set_level(int new_level);

    void server_update(nlohmann::json entity_info);
    void init() override;
    void update() override;
};

#endif