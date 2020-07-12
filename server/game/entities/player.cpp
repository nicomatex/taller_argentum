#include "player.h"

#include <cmath>
#include <cstdlib>
#include <vector>

#include "../../configuration_manager.h"
#include "../items/potion.h"
#include "../map_log_factory.h"
#include "components/player_combat_component.h"
#include "components/player_movement_component.h"

#define DEAD_HEAD_ID 9
#define DEAD_BODY_ID 5

// Temp
#include <iostream>

Player::Player(EntityId entity_id, nlohmann::json player_info, Map& map)
    : Entity(entity_id, player_info["name"], player_info["curr_level"],
             player_info["curr_exp"]),
      alive(player_info["alive"]),
      head_id(player_info["head_id"]),
      body_id(player_info["body_id"]),
      inventory(player_info["inventory"]),
      map(map),
      class_type(player_info["class_type"]),
      race_type(player_info["race_type"]) {
    movement_component = new PlayerMovementComponent(7);
    combat_component = new PlayerCombatComponent(
        player_info["helmet_id"], player_info["armor_id"],
        player_info["shield_id"], player_info["weapon_id"],
        player_info["curr_hp"], player_info["curr_mp"],
        AttributeManager::create_stats(player_info["race_type"]), *this,
        ConfigurationManager::get_player_attack_speed());
}

void Player::update(uint64_t delta_t) {
    position_t steps = movement_component->update(delta_t);
    combat_component->update(delta_t);
    map.move(this->id, steps);
}

entity_type_t Player::get_type() const {
    return PLAYER;
}

class_type_t Player::get_class_type() const {
    return class_type;
}

race_type_t Player::get_race_type() const {
    return race_type;
}

nlohmann::json Player::get_data() const {
    nlohmann::json entity_data;
    entity_data["entity_id"] = id;
    entity_data["type_id"] = get_type();
    if (alive) {
        entity_data["head_id"] = head_id;
        entity_data["body_id"] = body_id;
    } else {
        entity_data["head_id"] = DEAD_HEAD_ID;
        entity_data["body_id"] = DEAD_BODY_ID;
    }
    entity_data["name"] = name;
    nlohmann::json aux = movement_component->get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    aux = combat_component->get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    aux = experience_component.get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    return entity_data;
}

nlohmann::json Player::get_inventory_data() const {
    return inventory.get_data();
}

void Player::use(SlotId slot) {
    Item* item;
    try {
        item = inventory.remove(slot, 1);
    } catch (...) {
        std::cout << "Excepcion lanzada" << std::endl;
        return;
    }
    item_type_t type = item->get_type();
    if (type == TYPE_ARMOR || type == TYPE_WEAPON) {
        Item* unequiped;
        if (type == TYPE_WEAPON) {
            unequiped = static_cast<PlayerCombatComponent*>(combat_component)
                            ->equip(static_cast<Weapon*>(item));
        } else {
            unequiped = static_cast<PlayerCombatComponent*>(combat_component)
                            ->equip(static_cast<Armor*>(item));
        }
        if (unequiped)
            try {
                inventory.add(unequiped);
            } catch (const FullItemContainerException& e) {
                std::cout << "Player Equip: ItemContainer full." << std::endl;
                /* tirar? no equipar? */
            }
    } else if (type == TYPE_POTION) {
        (static_cast<Potion*>(item))
            ->use(*static_cast<PlayerCombatComponent*>(combat_component));
        delete item;
    }
}

void Player::add_item(Item* item) {
    if (!item)
        return;
    try {
        if (item->get_type() == TYPE_GOLD) {
            float gold_max_sec_mult =
                ConfigurationManager::get_gold_max_sec_mult();
            float gold_max_sec_expo =
                ConfigurationManager::get_gold_max_sec_expo();
            float gold_exc_mult = ConfigurationManager::get_gold_exc_mult();
            Gold* gold = static_cast<Gold*>(item);
            unsigned int actual_gold = inventory.get_gold_stack();
            unsigned int max_secure_gold =
                (gold_max_sec_mult *
                 std::pow((double)get_level(), gold_max_sec_expo));
            if (actual_gold + gold->get_stack() <=
                max_secure_gold * gold_exc_mult) {
                inventory.add_gold(gold);
                delete item;
            } else {
                throw FullItemContainerException();
            }
        } else {
            inventory.add(item);
        }
        map.push_log(
            MapLogFactory::inventory_change(name, get_inventory_data()));
    } catch (const FullItemContainerException& e) {
        map.drop_loot(get_id(), item);
        map.push_log(MapLogFactory::inventory_full(name));
    }
}

Item* Player::remove_item(SlotId slot, uint32_t amount) {
    Item* item = nullptr;
    try {
        item = inventory.remove(slot, amount);
        map.push_log(
            MapLogFactory::inventory_change(name, get_inventory_data()));
    } catch (const EmptySlotException& e) {
    }
    return item;
}

Gold* Player::remove_gold(uint32_t amount) {
    Gold* gold = inventory.remove_gold(amount);
    map.push_log(MapLogFactory::inventory_change(name, get_inventory_data()));
    return gold;
}

uint32_t Player::get_gold_stack() const {
    return inventory.get_gold_stack();
}

void Player::unequip(SlotId slot) {
    PlayerCombatComponent* p_combat_component =
        static_cast<PlayerCombatComponent*>(combat_component);
    switch (slot) {
        case 0:
            add_item(p_combat_component->unequip_helmet());
            break;
        case 1:
            add_item(p_combat_component->unequip_chest());
            break;
        case 2:
            add_item(p_combat_component->unequip_shield());
            break;
        case 3:
            add_item(p_combat_component->unequip_weapon());
            break;
        default:
            add_item(p_combat_component->unequip_helmet());
            add_item(p_combat_component->unequip_chest());
            add_item(p_combat_component->unequip_shield());
            add_item(p_combat_component->unequip_weapon());
            break;
    }
}

nlohmann::json Player::get_persist_data() const {
    nlohmann::json entity_data;
    entity_data["head_id"] = head_id;
    entity_data["body_id"] = body_id;
    entity_data["name"] = name;
    entity_data["inventory"] = inventory.get_persist_data();
    entity_data["class_type"] = class_type;
    entity_data["race_type"] = race_type;
    entity_data["alive"] = alive;
    nlohmann::json aux = static_cast<PlayerCombatComponent*>(combat_component)
                             ->get_persist_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    aux = experience_component.get_persist_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    return entity_data;
}

void Player::set_movement(mov_action_t action, direction_t direction) {
    static_cast<PlayerMovementComponent*>(movement_component)
        ->set_movement(action, direction);
}

void Player::revive() {
    alive = true;
    regen_max();
}

void Player::regen_max() {
    static_cast<PlayerCombatComponent*>(combat_component)->regen_max();
}

void Player::die() {
    experience_component.reduce();
    alive = false;
    std::vector<Item*> drops = inventory.remove_all();
    float gold_max_sec_mult = ConfigurationManager::get_gold_max_sec_mult();
    float gold_max_sec_expo = ConfigurationManager::get_gold_max_sec_expo();
    unsigned int actual_gold = inventory.get_gold_stack();
    unsigned int max_secure_gold =
        (gold_max_sec_mult * std::pow((double)get_level(), gold_max_sec_expo));
    if (actual_gold > max_secure_gold) {
        drops.push_back(inventory.remove_gold(actual_gold - max_secure_gold));
    }
    PlayerCombatComponent* p_combat_component =
        static_cast<PlayerCombatComponent*>(combat_component);
    Weapon* weapon = p_combat_component->unequip_weapon();
    if (weapon)
        drops.push_back(weapon);
    Armor* helmet = p_combat_component->unequip_helmet();
    if (helmet)
        drops.push_back(helmet);
    Armor* chest = p_combat_component->unequip_chest();
    if (chest)
        drops.push_back(chest);
    Armor* shield = p_combat_component->unequip_shield();
    if (shield)
        drops.push_back(shield);
    map.drop_loot(id, drops);
    map.push_log(MapLogFactory::inventory_change(name, get_inventory_data()));
}

bool Player::is_alive() const {
    return alive;
}

bool Player::can_attack(Entity* attacked) const {
    if (!combat_component->attack_ready())
        return false;
    if (attacked->get_type() == MONSTER)
        return true;
    else if (attacked->get_type() == NPC)
        return false;
    Player* player = static_cast<Player*>(attacked);
    unsigned int newbie_lvl = ConfigurationManager::get_newbie_lvl();
    unsigned int max_lvl_diff = ConfigurationManager::get_max_level_diff();
    return (player->get_level() > newbie_lvl) && (get_level() > newbie_lvl) &&
           (std::abs(static_cast<int>(get_level() - player->get_level())) <
            max_lvl_diff);
}
