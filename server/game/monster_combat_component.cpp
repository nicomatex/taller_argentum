#include "monster_combat_component.h"

#include "actions/action_attack.h"

MonsterCombatComponent::MonsterCombatComponent(unsigned int max_hp,
                                               unsigned int damage,
                                               float attack_speed, Map& map,
                                               EntityId entity_id)
    : CombatComponent(max_hp, 0),
      damage(damage),
      map(map),
      entity_id(entity_id) {}
MonsterCombatComponent::~MonsterCombatComponent() {}

damage_t MonsterCombatComponent::attack() {
    return {(int)damage, false};
}

attack_result_t MonsterCombatComponent::receive_damage(damage_t raw_damage) {
    return {true, raw_damage.damage, false, false};
}

void MonsterCombatComponent::update(uint64_t delta_t) {
    int time_between_attacks = 1000 / attack_speed;
    if (attack_accumulator >= time_between_attacks) {
        map.push_action(entity_id, new ActionAttack());
        attack_accumulator = attack_accumulator % time_between_attacks;
    } else {
        attack_accumulator += delta_t;
    }
}

bool MonsterCombatComponent::attack_ready() const {
    return true;
}
