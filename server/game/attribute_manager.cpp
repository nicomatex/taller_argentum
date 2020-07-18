#include "attribute_manager.h"

#include <fstream>
#include <iostream>

#include "../../include/my_exception.h"

stats_t AttributeManager::stats;
std::unordered_map<race_type_t, std::string> AttributeManager::race_names_map;
std::unordered_map<race_type_t, nlohmann::json>
    AttributeManager::race_modif_map;
std::unordered_map<race_type_t, nlohmann::json>
    AttributeManager::race_multi_map;

std::unordered_map<class_type_t, std::string> AttributeManager::class_names_map;
std::unordered_map<class_type_t, nlohmann::json>
    AttributeManager::class_multi_map;

AttributeManager::AttributeManager() {}

AttributeManager::~AttributeManager() {}

void AttributeManager::init(const char *stats_file, const char *races_file,
                            const char *classes_file) {
    std::ifstream stats_istream(stats_file);
    if (!stats_istream.is_open())
        throw MyException("AtributeManager: Error opening stats file: %s",
                          stats_file);
    nlohmann::json json_stats;
    stats_istream >> json_stats;
    stats = json_stats["stats"];

    std::ifstream races_istream(races_file);
    if (!races_istream.is_open())
        throw MyException("AtributeManager: Error opening races file: %s",
                          races_file);
    nlohmann::json json_races;
    races_istream >> json_races;
    for (auto &it : json_races["races"].items()) {
        nlohmann::json race_data = it.value();
        race_type_t race_type = race_data["type"];
        race_names_map[race_type] = race_data["name"];
        race_modif_map[race_type] = race_data["stats_modifiers"];
        race_multi_map[race_type] = race_data["multipliers"];
    }

    std::ifstream classes_istream(classes_file);
    if (!classes_istream.is_open())
        throw MyException("AtributeManager: Error opening classes file: %s",
                          classes_file);
    nlohmann::json json_classes;
    classes_istream >> json_classes;
    for (auto &it : json_classes["classes"].items()) {
        nlohmann::json class_data = it.value();
        class_type_t class_type = class_data["type"];
        class_names_map[class_type] = class_data["name"];
        class_multi_map[class_type] = class_data["multipliers"];
    }
}

stats_t AttributeManager::create_stats(race_type_t race_type) {
    if (!race_exists(race_type))
        throw MyException("AttributeManager: Race does not exist: %i",
                          race_type);
    const nlohmann::json &stats_modifiers = race_modif_map.at(race_type);
    stats_t new_stats = stats;
    new_stats.strength += int(stats_modifiers["strength"]);
    new_stats.agility += int(stats_modifiers["agility"]);
    new_stats.intelligence += int(stats_modifiers["intelligence"]);
    new_stats.physique += int(stats_modifiers["physique"]);
    return new_stats;
}

bool AttributeManager::race_exists(race_type_t race_type) {
    return race_names_map.count(race_type);
}

bool AttributeManager::class_exists(class_type_t class_type) {
    return class_names_map.count(class_type);
}

float AttributeManager::get_race_hp_multiplier(race_type_t race_type) {
    if (!race_exists(race_type))
        throw MyException("AttributeManager: Race does not exist: %i",
                          race_type);
    return float(race_multi_map.at(race_type)["health_multiplier"]);
}

float AttributeManager::get_race_mp_multiplier(race_type_t race_type) {
    if (!race_exists(race_type))
        throw MyException("AttributeManager: Race does not exist: %i",
                          race_type);
    return float(race_multi_map.at(race_type)["mana_multiplier"]);
}

float AttributeManager::get_regen_multiplier(race_type_t race_type) {
    if (!race_exists(race_type))
        throw MyException("AttributeManager: Race does not exist: %i",
                          race_type);
    return float(race_multi_map.at(race_type)["regen_multiplier"]);
}

float AttributeManager::get_class_hp_multiplier(class_type_t class_type) {
    if (!class_exists(class_type))
        throw MyException("AttributeManager: Class does not exist: %i",
                          class_type);
    return float(class_multi_map.at(class_type)["health_multiplier"]);
}

float AttributeManager::get_class_mp_multiplier(class_type_t class_type) {
    if (!class_exists(class_type))
        throw MyException("AttributeManager: Class does not exist: %i",
                          class_type);
    return float(class_multi_map.at(class_type)["mana_multiplier"]);
}

float AttributeManager::get_meditate_multiplier(class_type_t class_type) {
    if (!class_exists(class_type))
        throw MyException("AttributeManager: Class does not exist: %i",
                          class_type);
    return float(class_multi_map.at(class_type)["meditate_multiplier"]);
}