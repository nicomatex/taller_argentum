#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

typedef enum { helmet, chest, shield } slot_info_t;

typedef struct armor_info {
    uint16_t min_defense;
    uint16_t max_defense;
    slot_info_t slot_info;
} armor_info_t;

inline void to_json(nlohmann::json& j, const armor_info_t& a) {
    j["min_defense"] = a.min_defense;
    j["max_defense"] = a.max_defense;
    j["slot_info"] = a.slot_info;
}

inline void from_json(const nlohmann::json& j, armor_info_t& a) {
    j["min_defense"].get_to(a.min_defense);
    j["max_defense"].get_to(a.max_defense);
    j["slot_info"].get_to(a.slot_info);
}

class Armor : public Item {
   private:
    armor_info_t armor_info;

   public:
    Armor();
    Armor(item_info_t item_info, armor_info_t armor_info, uint32_t stack = 0);
    int reduce_damage(int damage);
    nlohmann::json get_data() const override;
    slot_info_t get_slot() const;
    ~Armor();
};

#endif  // ARMOR_H