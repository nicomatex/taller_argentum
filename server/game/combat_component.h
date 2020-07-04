#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include "../../include/nlohmann/json.hpp"
#include "items/armor.h"
#include "items/weapon.h"

typedef struct damage {
    int damage;
    bool crit;
} damage_t;

typedef struct attack_result {
    bool success;
    int damage_dealt;
    bool dodged;
    bool killed;
} attack_result_t;

class CombatComponent {
   protected:
    const unsigned int max_hp;
    unsigned int current_hp;
    const unsigned int max_mp;
    unsigned int current_mp;

    float attack_speed;  // en golpes / segundo.
    int attack_accumulator;

    Armor* helmet;
    Armor* armor;
    Armor* shield;
    Weapon* weapon;

   public:
    CombatComponent(ItemId helmet_id, ItemId armor_id, ItemId shield_id,
                    ItemId weapon_id, unsigned int current_hp,
                    unsigned int current_mp, float attack_speed);

    virtual ~CombatComponent();

    damage_t attack();

    // int special();
    void update(uint64_t);

    attack_result_t receive_damage(damage_t raw_damage);

    /* Devuelve true si esta listo para atacar. */
    bool attack_ready() const;

    Armor* equip(Armor* armor);
    Weapon* equip(Weapon* weapon);

    nlohmann::json get_data() const;
    nlohmann::json get_persist_data() const;
};

#endif  // COMBAT_COMPONENT_H
