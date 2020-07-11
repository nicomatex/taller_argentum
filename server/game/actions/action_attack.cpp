#include "action_attack.h"

#include "../map.h"
#include "../map_log_factory.h"
#include "../position.h"

ActionAttack::ActionAttack() {}

void ActionAttack::execute(Map& map, EntityId entity_id) const {
    Entity* attacker = Action::get_entity(map, entity_id);
    if (!attacker || !attacker->is_alive())
        return;
    position_t attacked_pos =
        attacker->get_facing_position(map.get_position(entity_id));
    Entity* attacked = Action::get_entity(map, attacked_pos);
    if (!attacked || !attacked->is_alive() || !attacker->can_attack(attacked))
        return;
    attack_result_t result = attacker->attack(attacked);
    if (attacker->get_type() == PLAYER)
        map.push_log(MapLogFactory::deal_damage(
            attacker->get_name(), {{"damage", result.damage_dealt},
                                   {"dodged", result.dodged},
                                   {"to", attacked->get_name()},
                                   {"to_id", attacked->get_id()}}));
    if (attacked->get_type() == PLAYER)
        map.push_log(MapLogFactory::receive_damage(
            attacked->get_name(), {{"damage", result.damage_dealt},
                                   {"dodged", result.dodged},
                                   {"from", attacker->get_name()}}));
    if (result.killed) {
        attacked->die();
        if (attacked->get_type() == MONSTER)
            map.rm_entity(attacked->get_id());
    }
}
