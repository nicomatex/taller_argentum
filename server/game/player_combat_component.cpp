#include "player_combat_component.h"

#include "../server_manager.h"
#include "items/item.h"
#include "items/item_factory.h"

// Temp

#define NOT_EQUIPED 0

PlayerCombatComponent::PlayerCombatComponent(
    ItemId helmet_id, ItemId armor_id, ItemId shield_id, ItemId weapon_id,
    unsigned int current_hp, unsigned int current_mp, stats_t stats,
    Player& player, float attack_speed)
    : CombatComponent(stats.physique *
                     AttributeManager::get_class_hp_multiplier(
                         player.get_class_type()) *
                     AttributeManager::get_race_hp_multiplier(
                         player.get_race_type()) *
                     player.get_level(),
                     stats.intelligence *
                     AttributeManager::get_class_mp_multiplier(
                         player.get_class_type()) *
                     AttributeManager::get_race_mp_multiplier(
                         player.get_race_type()) *
                     player.get_level(),
                    current_hp, current_mp),
      player(player),
      stats(stats),
      attack_speed(attack_speed),
      attack_accumulator(0),
      helmet(nullptr),
      armor(nullptr),
      shield(nullptr),
      weapon(nullptr) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    if (helmet_id)
        helmet = static_cast<Armor*>(item_factory.create(helmet_id, 1));
    if (armor_id)
        armor = static_cast<Armor*>(item_factory.create(armor_id, 1));
    if (shield_id)
        shield = static_cast<Armor*>(item_factory.create(shield_id, 1));
    if (weapon_id)
        weapon = static_cast<Weapon*>(item_factory.create(weapon_id, 1));
}

PlayerCombatComponent::~PlayerCombatComponent() {
    delete helmet;
    delete armor;
    delete shield;
    delete weapon;
}

damage_t PlayerCombatComponent::attack() {
    attack_accumulator = 0;
    // TODO: critical strike
    if (weapon)
        return {weapon->deal_damage(), 0};
    return {10, 0};
}

attack_result_t PlayerCombatComponent::receive_damage(damage_t raw_damage) {
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

nlohmann::json PlayerCombatComponent::get_data() const {
    nlohmann::json data = CombatComponent::get_data();
    data["helmet_id"] = helmet ? helmet->get_sprite_id() : NOT_EQUIPED;
    data["armor_id"] = armor ? armor->get_sprite_id() : NOT_EQUIPED;
    data["shield_id"] = shield ? shield->get_sprite_id() : NOT_EQUIPED;
    data["weapon_id"] = weapon ? weapon->get_sprite_id() : NOT_EQUIPED;
    return data;
}

nlohmann::json PlayerCombatComponent::get_persist_data() const {
    nlohmann::json data;
    data["curr_hp"] = current_hp;
    data["curr_mp"] = current_mp;
    data["helmet_id"] = helmet ? helmet->get_id() : NOT_EQUIPED;
    data["armor_id"] = armor ? armor->get_id() : NOT_EQUIPED;
    data["shield_id"] = shield ? shield->get_id() : NOT_EQUIPED;
    data["weapon_id"] = weapon ? weapon->get_id() : NOT_EQUIPED;
    return data;
}

void PlayerCombatComponent::update(uint64_t delta_t) {
    int time_between_attacks = 1000 / attack_speed;
    if (attack_accumulator < time_between_attacks)
        attack_accumulator += delta_t;
}

bool PlayerCombatComponent::attack_ready() const {
    int time_between_attacks = 1000 / attack_speed;
    return attack_accumulator >= time_between_attacks;
}

Armor* PlayerCombatComponent::equip(Armor* new_armor) {
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

Weapon* PlayerCombatComponent::equip(Weapon* new_weapon) {
    Weapon* old = weapon;
    weapon = new_weapon;
    return old;
}
