#ifndef __STATS_COMPONENT_H
#define __STATS_COMPONENT_H

#include <unordered_map>
#include <mutex>
#include "../ECS/component.h"

typedef std::unordered_map<std::string,unsigned int> StatValues;

class StatsComponent:public Component{
    private:
        StatValues max_stat_values;
        StatValues current_stat_values;
        std::mutex m;
        
    public:
        StatsComponent(int max_hp, int current_hp, int max_mp, int current_mp);

        unsigned int get_stat_current_value(const std::string &stat_name);
        unsigned int get_stat_max_value(const std::string &stat_name);

        void set_stat_current_value(const std::string &stat_name, unsigned int new_value);
        void set_stat_max_value(const std::string &stat_name, unsigned int new_value);
        void init() override;
        void update() override;
};


#endif