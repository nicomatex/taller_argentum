#include "player.h"

#include <cstdlib>
#include <vector>

#include "../items/potion.h"
#include "../map_log_factory.h"
#include "components/player_combat_component.h"
#include "components/player_movement_component.h"

#define DEAD_HEAD_ID 9
#define DEAD_BODY_ID 5
#define NEWBIE_LVL 12
#define LVL_DIFFERENCE 10

#define GOLD_MAX_MULT 100
#define GOLD_MAX_EXP 1.1
#define GOLD_EXCESS 1.5

// Temp
#include <iostream>

Player::Player(EntityId entity_id, nlohmann::json player_info, Map& map)
    : Entity(entity_id, player_info["name"], player_info["curr_level"],
             player_info["curr_exp"]),
      head_id(player_info["head_id"]),
      body_id(player_info["body_id"]),
      inventory(player_info["inventory"]),
      map(map),
      class_type(player_info["class_type"]),
      race_type(player_info["race_type"]),
      alive(player_info["alive"]) {
    movement_component = new PlayerMovementComponent(7);
    combat_component = new PlayerCombatComponent(
        player_info["helmet_id"], player_info["armor_id"],
        player_info["shield_id"], player_info["weapon_id"],
        player_info["curr_hp"], player_info["curr_mp"],
        AttributeManager::create_stats(player_info["race_type"]), *this, 2);
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
            Gold* gold = static_cast<Gold*>(item);
            unsigned int actual_gold = inventory.get_gold_stack();
            unsigned int max_secure_gold =
                (GOLD_MAX_MULT * std::pow((double)get_level(), GOLD_MAX_EXP));
            if (actual_gold + gold->get_stack() <=
                max_secure_gold * GOLD_EXCESS) {
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

void Player::unequip() {
    PlayerCombatComponent* p_combat_component =
        static_cast<PlayerCombatComponent*>(combat_component);
    add_item(p_combat_component->unequip_helmet());
    add_item(p_combat_component->unequip_chest());
    add_item(p_combat_component->unequip_shield());
    add_item(p_combat_component->unequip_weapon());
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
    static_cast<PlayerCombatComponent*>(combat_component)->regen_max();
}

void Player::die() {
    experience_component.reduce();
    alive = false;
    std::vector<Item*> drops = inventory.remove_all();
    unsigned int actual_gold = inventory.get_gold_stack();
    unsigned int max_secure_gold =
        (GOLD_MAX_MULT * std::pow((double)get_level(), GOLD_MAX_EXP));
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
    if (attacked->get_type() == MONSTER)
        return true;
    else if (attacked->get_type() == NPC)
        return false;
    Player* player = static_cast<Player*>(attacked);
    return (player->get_level() > NEWBIE_LVL) && (get_level() > NEWBIE_LVL) &&
           (std::abs<int>(get_level() - player->get_level()) < LVL_DIFFERENCE);
}
