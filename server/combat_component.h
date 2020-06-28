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

    float attack_speed; // en golpes / segundo.
    int attack_accumulator;

    int helmet_id;
    int armor_id;
    int shield_id;
    int weapon_id;

   public:
    CombatComponent(int helmet, int armor, int shield, int weapon, float attack_speed);
    virtual ~CombatComponent();

    damage_t attack();

    // int special();
    void update(uint64_t);

    attack_result_t receive_damage(damage_t raw_damage);

    /* Devuelve true si esta listo para atacar. */
    bool attack_ready() const;

    nlohmann::json get_data() const;
};

#endif  // COMBAT_COMPONENT_H
