#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include <tuple>

#include "../../../../include/nlohmann/json.hpp"

typedef struct attack {
    int damage;
    bool crit;
} attack_t;

typedef struct attack_result {
    int damage_dealt;
    bool dodged;
    bool killed;
} attack_result_t;

class CombatComponent {
   protected:
    unsigned int max_hp;
    unsigned int max_mp;
    unsigned int current_hp;
    unsigned int current_mp;

   public:
    CombatComponent(unsigned int max_hp, unsigned int max_mp);
    CombatComponent(unsigned int max_hp, unsigned int max_mp,
                    unsigned int current_hp, unsigned int current_mp);
    virtual ~CombatComponent();

    void reset_max(unsigned int max_hp, unsigned int max_mp);
    unsigned int restore_hp(unsigned int hp);

    bool can_spend_mp(unsigned int mp);
    void spend_mp(unsigned int mp);

    virtual attack_t attack() = 0;
    virtual attack_result_t receive_damage(attack_t raw_damage) = 0;

    virtual void update(uint64_t) = 0;

    unsigned int get_max_hp() const;

    /* Devuelve true si esta listo para atacar. */
    virtual bool attack_ready() const = 0;

    virtual nlohmann::json get_data() const;

    void set_max_mp(unsigned int mp);

    void set_max_hp(unsigned int hp);
};

#endif  // COMBAT_COMPONENT_H
