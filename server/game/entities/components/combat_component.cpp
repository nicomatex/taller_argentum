#include "combat_component.h"

CombatComponent::CombatComponent(unsigned int max_hp, unsigned int max_mp)
    : max_hp(max_hp), max_mp(max_mp), current_hp(max_hp), current_mp(max_mp) {}
CombatComponent::CombatComponent(unsigned int max_hp, unsigned int max_mp,
                                 unsigned int current_hp,
                                 unsigned int current_mp)
    : max_hp(max_hp),
      max_mp(max_mp),
      current_hp(current_hp),
      current_mp(current_mp) {}

CombatComponent::~CombatComponent() {}

unsigned int CombatComponent::get_max_hp() const {
    return max_hp;
}

void CombatComponent::reset_max(unsigned int new_max_hp,
                                unsigned int new_max_mp) {
    max_hp = new_max_hp;
    max_mp = new_max_mp;
    current_hp = new_max_hp;
    current_mp = new_max_mp;
}

nlohmann::json CombatComponent::get_data() const {
    nlohmann::json data;
    data["max_hp"] = max_hp;
    data["max_mp"] = max_mp;
    data["curr_hp"] = current_hp;
    data["curr_mp"] = current_mp;
    return data;
}
