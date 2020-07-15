#include "player_combat_component.h"

#include <cmath>
#include <random>

#include "../../../configuration_manager.h"
#include "../../../server_manager.h"
#include "../../items/item.h"
#include "../../items/item_factory.h"
#include "../../items/weapon.h"

// Temp

#define NOT_EQUIPED 0

PlayerCombatComponent::PlayerCombatComponent(ItemId helmet_id, ItemId armor_id,
                                             ItemId shield_id, ItemId weapon_id,
                                             unsigned int current_hp,
                                             unsigned int current_mp,
                                             stats_t stats, Player& player,
                                             float attack_speed)
    : CombatComponent(
          stats.physique *
              AttributeManager::get_class_hp_multiplier(
                  player.get_class_type()) *
              AttributeManager::get_race_hp_multiplier(player.get_race_type()) *
              player.get_level(),
          stats.intelligence *
              AttributeManager::get_class_mp_multiplier(
                  player.get_class_type()) *
              AttributeManager::get_race_mp_multiplier(player.get_race_type()) *
              player.get_level(),
          current_hp, current_mp),
      player(player),
      stats(stats),
      attack_speed(attack_speed),
      attack_accumulator(0),
      regen_counter(0),
      helmet(nullptr),
      armor(nullptr),
      shield(nullptr),
      weapon(nullptr),
      is_meditating(false),
      meditate_counter(0),
      is_resuscitating(false),
      resuscitate_counter(0) {
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

std::vector<map_log_t> PlayerCombatComponent::use_ability(Entity* target,
                                                          position_t source,
                                                          position_t dest) {
    if (!weapon)
        return std::vector<map_log_t>{};
    return weapon->use_ability(&player, target, source, dest);
}

attack_t PlayerCombatComponent::attack() {
    attack_accumulator = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    unsigned int critic_prob = ConfigurationManager::get_critic_prob();
    float critic_mult = ConfigurationManager::get_critic_mult();
    bool is_critic = (gen() % 100) < critic_prob;
    int damage = stats.strength;
    if (weapon)
        damage += weapon->deal_damage();
    if (is_critic)
        damage *= critic_mult;
    return {damage, is_critic};
}

attack_result_t PlayerCombatComponent::receive_damage(attack_t attack) {
    attack_result_t result = {attack.damage, false, false};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);
    double dodge_threshold = ConfigurationManager::get_dodge_thold();
    if (!attack.crit &&
        (std::pow(dist(gen), stats.agility) < dodge_threshold)) {
        result = {0, true, false};
    }
    int received_dmg = attack.damage;
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
        current_mp = 0;
        result.killed = true;
    } else {
        current_hp -= result.damage_dealt;
    }
    return result;
}

nlohmann::json PlayerCombatComponent::get_data() const {
    nlohmann::json data = CombatComponent::get_data();
    if (helmet) {
        data["helmet_id"] = helmet->get_sprite_id();
        data["helmet_info"] = helmet->get_data()["armor_info"];
        data["helmet_info"].erase("slot_info");
    } else {
        data["helmet_id"] = NOT_EQUIPED;
    }
    if (armor) {
        data["armor_id"] = armor->get_sprite_id();
        data["armor_info"] = armor->get_data()["armor_info"];
        data["armor_info"].erase("slot_info");
    } else {
        data["armor_id"] = NOT_EQUIPED;
    }
    if (shield) {
        data["shield_id"] = shield->get_sprite_id();
        data["shield_info"] = shield->get_data()["armor_info"];
        data["shield_info"].erase("slot_info");
    } else {
        data["shield_id"] = NOT_EQUIPED;
    }
    if (weapon) {
        data["weapon_id"] = weapon->get_sprite_id();
        data["weapon_info"] = weapon->get_data()["weapon_info"];
    } else {
        data["weapon_id"] = NOT_EQUIPED;
    }
    data["is_meditating"] = is_meditating;
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
    max_hp =  stats.physique *
              AttributeManager::get_class_hp_multiplier(
                  player.get_class_type()) *
              AttributeManager::get_race_hp_multiplier(player.get_race_type()) *
              player.get_level();
    max_mp = stats.intelligence *
              AttributeManager::get_class_mp_multiplier(
                  player.get_class_type()) *
              AttributeManager::get_race_mp_multiplier(player.get_race_type()) *
              player.get_level();

    if (is_resuscitating) {
        resuscitate_counter -= delta_t;
        if (resuscitate_counter <= 0) {
            is_resuscitating = false;
            player.set_alive(true);
            regen_max();
        }
        return;
    }

    float curr_attack_speed =
        weapon ? weapon->get_attack_speed() : attack_speed;
    uint32_t time_between_attacks = UINT32_MAX;
    if (curr_attack_speed != 0)
        time_between_attacks = 1000 / curr_attack_speed;
    if (attack_accumulator < time_between_attacks)
        attack_accumulator += delta_t;
    if (player.is_alive()) {
        regen_counter += delta_t;
        if (regen_counter >= 1000) {
            float regen_multiplier =
                AttributeManager::get_regen_multiplier(player.get_race_type());
            regen(regen_multiplier, regen_multiplier);
            regen_counter = 0;
        } else {
            regen_counter += delta_t;
        }
    }

    if (is_meditating) {
        meditate_counter += delta_t;
        if (meditate_counter >= 1000) {
            float meditate_multiplier =
                AttributeManager::get_meditate_multiplier(
                    player.get_class_type());
            regen_mp(meditate_multiplier * stats.intelligence);
            meditate_counter = 0;
        } else {
            meditate_counter += delta_t;
        }
        if (current_mp == max_mp)
            is_meditating = false;
    }

}

void PlayerCombatComponent::resuscitate(int delta_t) {
    resuscitate_counter = delta_t;
    is_resuscitating = true;
}

bool PlayerCombatComponent::attack_ready() const {
    float curr_attack_speed =
        weapon ? weapon->get_attack_speed() : attack_speed;
    uint32_t time_between_attacks = UINT32_MAX;
    if (curr_attack_speed != 0)
        time_between_attacks = 1000 / curr_attack_speed;
    return attack_accumulator >= time_between_attacks;
}

Armor* PlayerCombatComponent::equip(Armor* new_armor) {
    Armor* old = nullptr;
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
Armor* PlayerCombatComponent::unequip_helmet() {
    Armor* unequiped = helmet;
    helmet = nullptr;
    return unequiped;
}

Armor* PlayerCombatComponent::unequip_chest() {
    Armor* unequiped = armor;
    armor = nullptr;
    return unequiped;
}

Armor* PlayerCombatComponent::unequip_shield() {
    Armor* unequiped = shield;
    shield = nullptr;
    return unequiped;
}

Weapon* PlayerCombatComponent::unequip_weapon() {
    Weapon* unequiped = weapon;
    weapon = nullptr;
    return unequiped;
}

void PlayerCombatComponent::regen_max() {
    current_hp = max_hp;
    current_mp = max_mp;
}

void PlayerCombatComponent::regen_hp(unsigned int amount_hp) {
    if (current_hp + amount_hp > max_hp)
        current_hp = max_hp;
    else
        current_hp += amount_hp;
}

void PlayerCombatComponent::regen_mp(unsigned int amount_mp) {
    if (current_mp + amount_mp > max_mp)
        current_mp = max_mp;
    else
        current_mp += amount_mp;
}

void PlayerCombatComponent::regen(unsigned int amount_hp,
                                  unsigned int amount_mp) {
    regen_hp(amount_hp);
    regen_mp(amount_mp);
}

void PlayerCombatComponent::set_meditate(bool meditating) {
    is_meditating = meditating;
}