#include "special_attack.h"

#include "../../configuration_manager.h"
#include "../map_log_factory.h"
#include "../random_event_generator.h"

SpecialAttack::SpecialAttack(uint32_t ability_id, uint16_t min_damage,
                             uint16_t max_damage, unsigned int mp_cost)
    : SpecialAbility(ability_id),
      min_damage(min_damage),
      max_damage(max_damage),
      mp_cost(mp_cost) {}

std::vector<map_log_t> SpecialAttack::execute(Player* caster, Entity* target,
                                              position_t source,
                                              position_t dest) const {
    std::vector<map_log_t> logs;
    if(!caster->can_spend_mp(mp_cost)) return logs;
    logs.push_back(MapLogFactory::special_ability(caster->get_name(),
                                                  ability_id, source, dest));
    caster->spend_mp(mp_cost);
    if (!target || !caster->can_attack(target) ||
        caster->get_id() == target->get_id())
        return logs;
    unsigned int max_lvl_diff = ConfigurationManager::get_max_level_diff();
    attack_result_t dealt = target->receive_damage(
        {RandomEventGenerator::random_in(min_damage, max_damage), true});
    caster->add_exp(
        dealt.damage_dealt *
        std::max<int>(target->get_level() - caster->get_level() + max_lvl_diff,
                      0));
    if (dealt.killed) {
        caster->add_exp(
            target->get_max_hp() *
            std::max<int>(
                target->get_level() - caster->get_level() + max_lvl_diff, 0));
    }
    logs.push_back(MapLogFactory::deal_damage(caster->get_name(),
                                              {{"damage", dealt.damage_dealt},
                                               {"dodged", dealt.dodged},
                                               {"to", target->get_name()},
                                               {"to_id", target->get_id()}}));
    if (target->get_type() == PLAYER)
        logs.push_back(MapLogFactory::receive_damage(
            target->get_name(), {{"damage", dealt.damage_dealt},
                                 {"dodged", dealt.dodged},
                                 {"from", caster->get_name()}}));
    if (dealt.killed) {
        target->die();
    }
    return logs;
}
