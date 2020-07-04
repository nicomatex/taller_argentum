#include "combat_component.h"

#include "../server_manager.h"
#include "items/item.h"
#include "items/item_factory.h"

#define NO_WEAPON 0

CombatComponent::CombatComponent(ItemId helmet_id, ItemId armor_id,
                                 ItemId shield_id, ItemId weapon_id,
                                 unsigned int current_hp,
                                 unsigned int current_mp, float attack_speed)
    : max_hp(100),
      max_mp(200),
      current_hp(current_hp),
      current_mp(current_mp),
      attack_speed(attack_speed),
      attack_accumulator(0) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    helmet = static_cast<Armor*>(item_factory.create(helmet_id, 1));
    armor = static_cast<Armor*>(item_factory.create(armor_id, 1));
    shield = static_cast<Armor*>(item_factory.create(shield_id, 1));
    if (weapon_id != NO_WEAPON)
        weapon = static_cast<Weapon*>(item_factory.create(weapon_id, 1));
}

CombatComponent::~CombatComponent() {
    delete helmet;
    delete armor;
    delete shield;
    delete weapon;
}

damage_t CombatComponent::attack() {
    attack_accumulator = 0;
    // TODO: critical strike
    if (weapon)
        return {weapon->deal_damage(), 0};
    return {10, 0};
}

attack_result_t CombatComponent::receive_damage(damage_t raw_damage) {
    attack_result_t result = {true, raw_damage.damage, false, false};
    // TODO: dodge
    int received_dmg = raw_damage.damage;
    if (helmet)
        received_dmg = helmet->reduce_damage(received_dmg);
    if (armor)
        received_dmg = armor->reduce_damage(received_dmg);
    if (shield)
        received_dmg = shield->reduce_damage(received_dmg);
    if (received_dmg < 0)
        received_dmg = 0;
    result.damage_dealt = received_dmg;

    if ((int)current_hp - result.damage_dealt <= 0) {
        current_hp = 0;
        result.killed = true;
    } else {
        current_hp -= result.damage_dealt;
    }
    return result;
}

nlohmann::json CombatComponent::get_data() const {
    nlohmann::json data;
    data["max_hp"] = max_hp;
    data["max_mp"] = max_mp;
    data["curr_hp"] = current_hp;
    data["curr_mp"] = current_mp;
    data["helmet_id"] = helmet->get_sprite_id();
    data["armor_id"] = armor->get_sprite_id();
    data["shield_id"] = shield->get_sprite_id();
    if (weapon)
        data["weapon_id"] = weapon->get_sprite_id();
    else
        data["weapon_id"] = NO_WEAPON;
    return data;
}

nlohmann::json CombatComponent::get_persist_data() const {
    nlohmann::json data;
    data["curr_hp"] = current_hp;
    data["curr_mp"] = current_mp;
    data["helmet_id"] = helmet->get_id();
    data["armor_id"] = armor->get_id();
    data["shield_id"] = shield->get_id();
    if (weapon)
        data["weapon_id"] = weapon->get_id();
    else
        data["weapon_id"] = NO_WEAPON;
    return data;
}

void CombatComponent::update(uint64_t delta_t) {
    int time_between_attacks = 1000 / attack_speed;
    if (attack_accumulator < time_between_attacks)
        attack_accumulator += delta_t;
}

bool CombatComponent::attack_ready() const {
    int time_between_attacks = 1000 / attack_speed;
    return attack_accumulator >= time_between_attacks;
}

Armor* CombatComponent::equip(Armor* new_armor) {
    Armor* old;
    switch (new_armor->get_slot()) {
        case 0:
            old = helmet;
            helmet = new_armor;
            break;
        case 1:
            old = armor;
            armor = new_armor;
            break;
        case 2:
            old = shield;
            shield = new_armor;
            break;
    }
    return old;
}

Weapon* CombatComponent::equip(Weapon* new_weapon) {
    Weapon* old = weapon;
    weapon = new_weapon;
    return old;
}
