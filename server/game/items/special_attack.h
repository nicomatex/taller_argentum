#ifndef SPECIAL_ATTACK_H
#define SPECIAL_ATTACK_H

#include <vector>

#include "../entities/components/player_combat_component.h"
#include "../entities/entity.h"
#include "../map_log_factory.h"
#include "special_ability.h"

class SpecialAttack : public SpecialAbility {
   private:
    uint16_t min_damage;
    uint16_t max_damage;
    unsigned int mp_cost;

   public:
    SpecialAttack(uint32_t special_id, uint16_t min_damage, uint16_t max_damage,
                  unsigned int mp_cost);

    std::vector<map_log_t> execute(Player* thrower, Entity* target,
                                   position_t source,
                                   position_t dest) const override;
};

#endif  // SPECIAL_ATTACK_H