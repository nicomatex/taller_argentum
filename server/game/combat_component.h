#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include "../../include/nlohmann/json.hpp"

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
    unsigned int max_hp;
    unsigned int current_hp;
    unsigned int max_mp;
    unsigned int current_mp;

   public:
    CombatComponent(unsigned int max_hp, unsigned int max_mp);
    CombatComponent(unsigned int max_hp, unsigned int max_mp,
                    unsigned int current_hp, unsigned int current_mp);
    virtual ~CombatComponent();

    void reset_max(unsigned int max_hp, unsigned int max_mp);

    virtual damage_t attack() = 0;
    virtual attack_result_t receive_damage(damage_t raw_damage) = 0;

    virtual void update(uint64_t) = 0;

    /* Devuelve true si esta listo para atacar. */
    virtual bool attack_ready() const = 0;

    virtual nlohmann::json get_data() const;
};

#endif  // COMBAT_COMPONENT_H
