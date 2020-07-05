#include "stats_component.h"

StatsComponent::StatsComponent(int max_hp, int current_hp, int max_mp,
                               int current_mp, int max_exp, int current_exp,
                               int level)
    : level(level) {
    max_stat_values["hp"] = max_hp;
    current_stat_values["hp"] = current_hp;

    max_stat_values["mp"] = max_mp;
    current_stat_values["mp"] = current_mp;

    max_stat_values["xp"] = max_exp;
    current_stat_values["xp"] = current_exp;
}

unsigned int StatsComponent::get_stat_current_value(
    const std::string &stat_name) {
    std::unique_lock<std::recursive_mutex> l(m);

    if (!current_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    return current_stat_values.at(stat_name);
}

unsigned int StatsComponent::get_stat_max_value(const std::string &stat_name) {
    std::unique_lock<std::recursive_mutex> l(m);
    if (!max_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    return max_stat_values.at(stat_name);
}

void StatsComponent::set_stat_max_value(const std::string &stat_name,
                                        unsigned int new_value) {
    std::unique_lock<std::recursive_mutex> l(m);
    if (!max_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    max_stat_values[stat_name] = new_value;
}

void StatsComponent::set_stat_current_value(const std::string &stat_name,
                                            unsigned int new_value) {
    std::unique_lock<std::recursive_mutex> l(m);
    if (!current_stat_values.count(stat_name)) {
        throw std::invalid_argument("Stat " + stat_name + "not found.");
    }
    current_stat_values[stat_name] = new_value;
}

void StatsComponent::update() {}

void StatsComponent::init() {}

void StatsComponent::set_level(int new_level) {
    std::unique_lock<std::recursive_mutex> l(m);
    level = new_level;
}

int StatsComponent::get_level() {
    std::unique_lock<std::recursive_mutex> l(m);
    return level;
}

void StatsComponent::server_update(nlohmann::json entity_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    set_stat_max_value("hp", entity_info["max_hp"]);
    set_stat_current_value("hp", entity_info["curr_hp"]);
    set_stat_max_value("mp", entity_info["max_mp"]);
    set_stat_current_value("mp", entity_info["curr_mp"]);
    set_stat_max_value("xp", entity_info["limit_exp"]);
    set_stat_current_value("xp", entity_info["curr_exp"]);
    set_level(entity_info["curr_level"]);
}