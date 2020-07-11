#include "npc_combat_component.h"
// Temp
#include <iostream>

const char* CantAttackNpcException::what() const throw() {
    return "No se puede atacar a un NPC!";
}

NpcCombatComponent::NpcCombatComponent() : CombatComponent(300, 0) {}
NpcCombatComponent::~NpcCombatComponent() {}

attack_t NpcCombatComponent::attack() {
    return {0, false};
}

attack_result_t NpcCombatComponent::receive_damage(attack_t raw_damage) {
    return {0, false, false};
}

void NpcCombatComponent::update(uint64_t delta_t) {}

bool NpcCombatComponent::attack_ready() const {
    return false;
}
