#include "action_attack.h"

#include "../map.h"
#include "../position.h"

ActionAttack::ActionAttack() {}
ActionAttack::~ActionAttack() {}

void ActionAttack::execute(Map& map, EntityId entity_id) const {
    Entity* attacker = Action::get_entity(map, entity_id);
    if (!attacker)  // || !attacker->is_alive() TODO
        return;
    position_t attacked_pos =
        attacker->get_facing_position(map.get_position(entity_id));
    Entity* attacked = Action::get_entity(map, attacked_pos);
    if (!attacked)  // || !attacked->is_alive() ||
                    // !attacker->can_attack(attacked) TODO
        return;
    attack_result_t result = attacker->attack(attacked);
    if (!result.success)
        return;
    if (result.killed)
        /* KILL, drops & give exp */;

    if (attacker->get_type() == PLAYER)
        map.push_log({{"log_type", 1},
                      {"player_name", attacker->get_name()},
                      {"damage", result.damage_dealt},
                      //   {"dodged", bool},
                      {"to", attacked->get_name()},
                      {"to_id", attacked->get_id()}});
    if (attacked->get_type() == PLAYER)
        map.push_log({{"log_type", 2},
                      {"player_name", attacked->get_name()},
                      {"damage", result.damage_dealt},
                      //   {"dodged", bool},
                      {"from", attacked->get_name()}});
}
