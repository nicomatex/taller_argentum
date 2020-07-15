#include "weapon.h"

#include "../random_event_generator.h"

Weapon::Weapon() {}

Weapon::Weapon(item_info_t item_info, weapon_info_t weapon_info,
               SpecialAbility* special, uint32_t stack)
    : Item(item_info, stack), weapon_info(weapon_info), special(special) {}

Weapon::Weapon(const Weapon& other, SpecialAbility* special)
    : Item(other), weapon_info(other.weapon_info), special(special) {}

Weapon::~Weapon() {
    delete special;
}

int Weapon::deal_damage() {
    return (int)RandomEventGenerator::random_in(weapon_info.min_damage,
                                                weapon_info.max_damage);
}

std::vector<map_log_t> Weapon::use_ability(Player* thrower, Entity* target,
                                           position_t source, position_t dest) {
    if (!special)
        return std::vector<map_log_t>{};
    return special->execute(thrower, target, source, dest);
}

float Weapon::get_attack_speed() {
    return weapon_info.attack_speed;
}

nlohmann::json Weapon::get_data() const {
    nlohmann::json info = Item::get_data();
    info["weapon_info"] = weapon_info;
    return info;
}
