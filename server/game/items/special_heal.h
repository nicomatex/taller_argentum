#ifndef SPECIAL_HEAL_H
#define SPECIAL_HEAL_H

#include <vector>

#include "../entities/components/player_combat_component.h"
#include "../entities/entity.h"
#include "../map.h"
#include "../map_log_factory.h"
#include "special_ability.h"

class SpecialHeal : public SpecialAbility {
   private:
    unsigned int heal_amount;
    unsigned int mp_cost;

   public:
    SpecialHeal(uint32_t ability_id, unsigned int heal_amount,
                unsigned int mp_cost);

    std::vector<map_log_t> execute(Player* thrower, Entity* target,
                                   position_t source,
                                   position_t dest) const override;
};

#endif  // SPECIAL_HEAL_H
