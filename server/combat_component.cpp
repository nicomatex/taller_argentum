#include "combat_component.h"

CombatComponent::CombatComponent(int helmet, int armor, int shield, int weapon)
    : max_hp(100),
      current_hp(max_hp),
      helmet_id(helmet),
      armor_id(armor),
      shield_id(shield),
      weapon_id(weapon) {}

CombatComponent::~CombatComponent() {}

nlohmann::json CombatComponent::get_data() const {
    nlohmann::json data;
    data["helmet_id"] = helmet_id;
    data["armor_id"] = armor_id;
    data["shield_id"] = shield_id;
    data["weapon_id"] = weapon_id;
    return data;
}
