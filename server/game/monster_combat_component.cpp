#include "monster_combat_component.h"

MonsterCombatComponent::MonsterCombatComponent(unsigned int max_hp,
                                               unsigned int damage)
    : CombatComponent(max_hp, 0), damage(damage) {}
MonsterCombatComponent::~MonsterCombatComponent() {}

damage_t MonsterCombatComponent::attack() {
    return {(int)damage, false};
}

attack_result_t MonsterCombatComponent::receive_damage(damage_t raw_damage) {
    return {true, 5, false, false};
}

void MonsterCombatComponent::update(uint64_t) {}

bool MonsterCombatComponent::attack_ready() const {
    return true;
}
