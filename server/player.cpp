#include "player.h"

#include "combat_component.h"
#include "movement_component.h"

// Temp
#include <iostream>

Player::Player(EntityId entity_id, nlohmann::json player_info, Map& map)
    : Entity(entity_id, player_info["name"], new MovementComponent(7),
             new CombatComponent(
                 player_info["helmet_id"], player_info["armor_id"],
                 player_info["shield_id"], player_info["weapon_id"])),
      head_id(player_info["head_id"]),
      body_id(player_info["body_id"]),
      map(map) {}

void Player::update(uint64_t delta_t) {
    position_t steps = movement_component->update(delta_t);
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
    return entity_data;
}

void Player::set_movement(mov_action_t action, direction_t direction) {
    movement_component->set_movement(action, direction);
}