#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include "../nlohmann/json.hpp"

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

    int attack();

    // int special();

    int receive_damage();

    nlohmann::json get_data() const;
};

#endif  // COMBAT_COMPONENT_H
