#include "player.h"

#include "player_combat_component.h"
#include "player_movement_component.h"

// Temp
#include <iostream>

Player::Player(EntityId entity_id, nlohmann::json player_info, Map& map)
    : Entity(entity_id, player_info["name"], new PlayerMovementComponent(7),
             new PlayerCombatComponent(
                 player_info["helmet_id"], player_info["armor_id"],
                 player_info["shield_id"], player_info["weapon_id"],
                 stats.physique *
                     AttributeManager::get_class_hp_multiplier(
                         player_info["class_type"]) *
                     AttributeManager::get_race_hp_multiplier(
                         player_info["race_type"]) *
                     experience_component.get_level(),
                 stats.intelligence *
                     AttributeManager::get_class_mp_multiplier(
                         player_info["class_type"]) *
                     AttributeManager::get_race_mp_multiplier(
                         player_info["race_type"]) *
                     experience_component.get_level(),
                 player_info["curr_hp"], player_info["curr_mp"], 2),
             player_info["curr_level"], player_info["curr_exp"]),
      head_id(player_info["head_id"]),
      body_id(player_info["body_id"]),
      inventory(player_info["inventory"]),
      map(map),
      stats(AttributeManager::create_stats(player_info["race_type"])),
      class_type(player_info["class_type"]),
      race_type(player_info["race_type"]) {}

void Player::update(uint64_t delta_t) {
    position_t steps = movement_component->update(delta_t);
    combat_component->update(delta_t);
    map.move(this->id, steps);

    // TODO: demas updates, como regeneraciones de vida/mana, etc.
}

entity_type_t Player::get_type() const {
    return PLAYER;
}

nlohmann::json Player::get_data() const {
    nlohmann::json entity_data;
    entity_data["entity_id"] = id;
    entity_data["type_id"] = get_type();
    entity_data["head_id"] = head_id;
    entity_data["body_id"] = body_id;
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
    std::cout << inventory.get_data() << std::endl;
    Item* item;
    try {
        item = inventory.remove(slot);
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
            } catch (const FullInventoryException& e) {
                std::cout << "Player Equip: Inventory full." << std::endl;
                /* tirar? no equipar? */
            }
    } else if (type == TYPE_POTION) {
        /* usar poción */
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