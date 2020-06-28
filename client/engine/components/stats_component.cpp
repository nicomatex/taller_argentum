#include "stats_component.h"

StatsComponent::StatsComponent(int max_hp, int current_hp, int max_mp,
                               int current_mp) {
    max_stat_values["hp"] = max_hp;
    current_stat_values["hp"] = current_hp;

    max_stat_values["mp"] = max_mp;
    current_stat_values["mp"] = current_mp;
}

unsigned int StatsComponent::get_stat_current_value(
    const std::string &stat_name) {
    std::unique_lock<std::mutex> l(m);

    if (!current_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    return current_stat_values.at(stat_name);
}

unsigned int StatsComponent::get_stat_max_value(const std::string &stat_name) {
    std::unique_lock<std::mutex> l(m);
    if (!max_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    return max_stat_values.at(stat_name);
}

void StatsComponent::set_stat_max_value(const std::string &stat_name,
                                        unsigned int new_value) {
    std::unique_lock<std::mutex> l(m);
    if (!max_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    max_stat_values[stat_name] = new_value;
}

void StatsComponent::set_stat_current_value(const std::string &stat_name,
                                            unsigned int new_value) {
    std::unique_lock<std::mutex> l(m);
    if (!current_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    current_stat_values[stat_name] = new_value;
}

void StatsComponent::update(){}

void StatsComponent::init(){}
