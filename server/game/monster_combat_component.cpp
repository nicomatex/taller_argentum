#include "monster_combat_component.h"

#include "actions/action_attack.h"

// Temp
#include <iostream>

MonsterCombatComponent::MonsterCombatComponent(unsigned int max_hp,
                                               unsigned int damage,
                                               float attack_speed, Map& map,
                                               EntityId entity_id)
    : CombatComponent(max_hp, 0),
      damage(damage),
      map(map),
      entity_id(entity_id),
      attack_accumulator(0),
      attack_speed(attack_speed) {}
MonsterCombatComponent::~MonsterCombatComponent() {}

damage_t MonsterCombatComponent::attack() {
    return {(int)damage, false};
}

attack_result_t MonsterCombatComponent::receive_damage(damage_t raw_damage) {
    attack_result_t result = {true, raw_damage.damage, false, false};
    if ((int)current_hp - result.damage_dealt <= 0) {
        current_hp = 0;
        result.killed = true;
    } else {
        current_hp -= result.damage_dealt;
    }
    return result;
}

void MonsterCombatComponent::update(uint64_t delta_t) {
    int time_between_attacks = 1000 / attack_speed;
    attack_accumulator += delta_t;
    if (attack_accumulator >= time_between_attacks) {
        map.push_action(entity_id, new ActionAttack());
        attack_accumulator = attack_accumulator % time_between_attacks;
    }
}

bool MonsterCombatComponent::attack_ready() const {
    return true;
}
