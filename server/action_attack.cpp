#include "action_attack.h"

#include "map.h"
#include "position.h"

// Temp
#include "event_factory.h"
#include "server_manager.h"

ActionAttack::ActionAttack() {}
ActionAttack::~ActionAttack() {}

void ActionAttack::execute(Map& map, EntityId entity_id) const {
    Entity* attacker = Action::get_entity(map, entity_id);
    if (!attacker)  // || !attacker->is_alive() TODO
        return;
    if (!attacker->attack_ready()) return;
    position_t attacked_pos =
        attacker->get_facing_position(map.get_position(entity_id));
    Entity* attacked = Action::get_entity(map, attacked_pos);
    if (!attacked)  // || !attacked->is_alive() TODO
        return;
    attack_result_t result = attacker->attack(attacked);
    if (result.killed)
        /* KILL, drops & give exp */;

    if (attacker->get_type() == PLAYER)
        map.push_log({{"player_name", attacker->get_name()},
                      {"str", "Attacado a " + attacked->get_name() + " por " +
                                  std::to_string(result.damage_dealt)}});
    if (attacked->get_type() == PLAYER)
        map.push_log(
            {{"player_name", attacked->get_name()},
             {"str", "Recibido " + std::to_string(result.damage_dealt) +
                         " de danio por " + attacker->get_name()}});
}
