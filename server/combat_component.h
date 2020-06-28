#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include "../nlohmann/json.hpp"

typedef struct damage {
    int damage;
    bool crit;
} damage_t;

typedef struct attack_result {
    int damage_dealt;
    bool dodged;
    bool killed;
} attack_result_t;

class CombatComponent {
   protected:
    const unsigned int max_hp;
    unsigned int current_hp;

    int helmet_id;
    int armor_id;
    int shield_id;
    int weapon_id;

   public:
    CombatComponent(int helmet, int armor, int shield, int weapon);
    virtual ~CombatComponent();

    damage_t attack();

    // int special();

    attack_result_t receive_damage(damage_t raw_damage);

    nlohmann::json get_data() const;
};

#endif  // COMBAT_COMPONENT_H
