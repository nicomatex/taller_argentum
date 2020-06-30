#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

typedef struct weapon_info {
    uint16_t min_damage;
    uint16_t max_damage;
} weapon_info_t;

inline void to_json(nlohmann::json& j, const weapon_info_t& w) {
    j["min_damage"] = w.min_damage;
    j["max_damage"] = w.max_damage;
}

inline void from_json(const nlohmann::json& j, weapon_info_t& w) {
    j["min_damage"].get_to(w.min_damage);
    j["max_damage"].get_to(w.max_damage);
}

class Weapon : public Item {
   private:
    weapon_info_t weapon_info;

   public:
    Weapon();
    Weapon(item_info_t item_info, weapon_info_t weapon_info,
           uint32_t stack = 0);
    int deal_damage();
    nlohmann::json get_data() override;
    ~Weapon();
};

#endif  // WEAPON_H