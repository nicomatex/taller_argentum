#include "combat_component.h"

CombatComponent::CombatComponent(int helmet, int armor, int shield, int weapon,
                                 float attack_speed)
    : max_hp(100),
      current_hp(max_hp),
      helmet_id(helmet),
      armor_id(armor),
      shield_id(shield),
      weapon_id(weapon),
      attack_speed(attack_speed),
      attack_accumulator(0) {}

CombatComponent::~CombatComponent() {}

damage_t CombatComponent::attack() {
    attack_accumulator = 0;
    return {15, 0};
}

attack_result_t CombatComponent::receive_damage(damage_t raw_damage) {
    attack_result_t result = {raw_damage.damage - 5, false, false};
    if (current_hp - result.damage_dealt <= 0) {
        current_hp = 0;
        result.killed = true;
    }
    // else if (dodged) TODO ANTES DEL CHECK DE DEAD
    //    result.dodged = true;
    else
        current_hp -= result.damage_dealt;
    return result;
}

nlohmann::json CombatComponent::get_data() const {
    nlohmann::json data;
    data["max_hp"] = max_hp;
    data["curr_hp"] = current_hp;
    data["helmet_id"] = helmet_id;
    data["armor_id"] = armor_id;
    data["shield_id"] = shield_id;
    data["weapon_id"] = weapon_id;
    return data;
}

void CombatComponent::update(uint64_t delta_t) {
    int time_between_attacks = 1000 / attack_speed;
    if (attack_accumulator < time_between_attacks) attack_accumulator += delta_t;
}

bool CombatComponent::attack_ready() const {
    int time_between_attacks = 1000 / attack_speed;
    return attack_accumulator >= time_between_attacks;
}