#ifndef SPECIAL_ABILITY_H
#define SPECIAL_ABILITY_H

#include <vector>

#include "../entities/components/player_combat_component.h"
#include "../entities/entity.h"
#include "../entities/player.h"
#include "../map_log_factory.h"

class SpecialAbility {
   protected:
    uint32_t ability_id;

   public:
    SpecialAbility(uint32_t ability_id);
    virtual ~SpecialAbility();

    virtual std::vector<map_log_t> execute(Player* thrower, Entity* target,
                                           position_t source,
                                           position_t dest) const = 0;
};

#endif  // SPECIAL_ABILITY_H
