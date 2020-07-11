#ifndef NPC_COMBAT_COMPONENT_H
#define NPC_COMBAT_COMPONENT_H

#include <exception>

#include "../../../../include/types.h"
#include "combat_component.h"

class CantAttackNpcException : public std::exception {
   public:
    const char *what() const throw();
};

class NpcCombatComponent : public CombatComponent {
   public:
    NpcCombatComponent();
    ~NpcCombatComponent();

    attack_t attack() override;
    attack_result_t receive_damage(attack_t attack) override;

    void update(uint64_t) override;

    /* Devuelve true si esta listo para atacar. */
    bool attack_ready() const override;
};

#endif  // NPC_COMBAT_COMPONENT_H
