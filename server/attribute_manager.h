#ifndef ATTRIBUTE_MANAGER_H
#define ATTRIBUTE_MANAGER_H

#include <unordered_map>

#include "../include/nlohmann/json.hpp"
#include "../include/types.h"

typedef struct stats {
    uint32_t strength;      // Fuerza
    uint32_t agility;       // Agilidad
    uint32_t intelligence;  // Inteligencia
    uint32_t physique;      // Constitucion
} stats_t;

inline void to_json(nlohmann::json &j, const stats_t &s) {
    j["strength"] = s.strength;
    j["agility"] = s.agility;
    j["intelligence"] = s.intelligence;
    j["physique"] = s.physique;
}

inline void from_json(const nlohmann::json &j, stats_t &s) {
    j["strength"].get_to(s.strength);
    j["agility"].get_to(s.agility);
    j["intelligence"].get_to(s.intelligence);
    j["physique"].get_to(s.physique);
}

class AttributeManager {
   private:
    static stats_t stats;
    static std::unordered_map<race_type_t, std::string> race_names_map;
    static std::unordered_map<race_type_t, nlohmann::json> race_modif_map;
    static std::unordered_map<race_type_t, nlohmann::json> race_multi_map;

    static std::unordered_map<class_type_t, std::string> class_names_map;
    static std::unordered_map<class_type_t, nlohmann::json> class_multi_map;
    static bool race_exists(race_type_t race_type);
    static bool class_exists(class_type_t class_type);

   public:
    AttributeManager();
    ~AttributeManager();

    static void init(const char *stats_file, const char *races_file,
                     const char *classes_file);

    // Player race methods
    static stats_t create_stats(race_type_t race_type);
    static std::string get_race_name(race_type_t race_type);
    static float get_race_hp_multiplier(race_type_t race_type);
    static float get_race_mp_multiplier(race_type_t race_type);
    static float get_regen_multiplier(race_type_t race_type);

    // Player class methods
    static std::string get_class_name(class_type_t class_type);
    static float get_class_hp_multiplier(class_type_t class_type);
    static float get_class_mp_multiplier(class_type_t class_type);
    static float get_meditate_multiplier(class_type_t class_type);
};

#endif  // ATTRIBUTE_MANAGER_H