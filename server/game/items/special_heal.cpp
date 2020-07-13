#include "special_heal.h"

#include "../map_log_factory.h"

SpecialHeal::SpecialHeal(uint32_t ability_id, unsigned int heal_amount,
                         unsigned int mp_cost)
    : SpecialAbility(ability_id), heal_amount(heal_amount), mp_cost(mp_cost) {}

std::vector<map_log_t> SpecialHeal::execute(Player* thrower, Entity* target,
                                            position_t source,
                                            position_t dest) const {
    std::vector<map_log_t> logs;
    if (!thrower->can_spend_mp(mp_cost))
        return logs;
    thrower->spend_mp(mp_cost);
    logs.push_back(MapLogFactory::special_ability(thrower->get_name(),
                                                  ability_id, source, dest));
    if (!target)
        return logs;
    // unsigned int healed =
    target->heal(heal_amount);
    // if (get_type() == PLAYER)
    //  LOG HEAL
    return logs;
}
