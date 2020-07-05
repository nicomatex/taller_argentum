#ifndef MONSTER_COMBAT_COMPONENT_H
#define MONSTER_COMBAT_COMPONENT_H

#include "../../include/types.h"
#include "combat_component.h"
#include "map.h"

class MonsterCombatComponent : public CombatComponent {
   private:
    unsigned int damage;
    float attack_speed;
    uint64_t attack_accumulator;
    Map& map;
    EntityId entity_id;

   public:
    MonsterCombatComponent(unsigned int max_hp, unsigned int damage,
                           float attack_speed, Map& map, EntityId entity_id);
    ~MonsterCombatComponent();

    damage_t attack() override;
    attack_result_t receive_damage(damage_t raw_damage) override;

    void update(uint64_t) override;

    /* Devuelve true si esta listo para atacar. */
    bool attack_ready() const override;
};

#endif  // MONSTER_COMBAT_COMPONENT_H
