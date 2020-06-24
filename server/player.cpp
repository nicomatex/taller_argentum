#include "player.h"

#include <iostream>

Player::Player(EntityId entity_id, nlohmann::json player_info, Map &map)
    : Entity(entity_id),
      head_id(player_info["head_id"]),
      body_id(player_info["body_id"]),
      name(player_info["name"]),
      helmet_id(player_info["helmet_id"]),
      armor_id(player_info["armor_id"]),
      shield_id(player_info["shield_id"]),
      weapon_id(player_info["weapon_id"]),
      map(map),
      move_accumulator(0),
      player_speed(5),
      current_direction(DOWN),
      moving(false) {}

void Player::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / player_speed;
    move_accumulator += delta_t;

    if (move_accumulator >= time_between_tiles) {
        int steps = move_accumulator /
                    time_between_tiles;  // Esto deberia dar 1 salvo que el
                                         // ciclo de juego se ponga MUY slow

        if (moving) {
            switch (current_direction) {
                case UP:
                    map.move(this->id, {0, -steps});
                    break;
                case DOWN:
                    map.move(this->id, {0, steps});
                    break;
                case RIGHT:
                    map.move(this->id, {steps, 0});
                    break;
                case LEFT:
                    map.move(this->id, {-steps, 0});
                    break;
                default:
                    break;
            }
        }

        /* Se guarda el restante para la proxima actualizacion. */
        if (moving && steps != 0) {
            move_accumulator = move_accumulator % time_between_tiles;
        } else {
            move_accumulator = time_between_tiles;
        }
    }

    // TODO: demas updates, como regeneraciones de vida/mana, etc.
}

entity_type_t Player::get_type() {
    return PLAYER;
}

nlohmann::json Player::get_data() {
    visual_entity_info["type_id"] = get_type();
    visual_entity_info["head_id"] = head_id;
    visual_entity_info["body_id"] = body_id;
    visual_entity_info["name"] = name;
    visual_entity_info["helmet_id"] = helmet_id;
    visual_entity_info["armor_id"] = armor_id;
    visual_entity_info["shield_id"] = shield_id;
    visual_entity_info["weapon_id"] = weapon_id;
    visual_entity_info["direction"] = current_direction;
    return visual_entity_info;
}

void Player::set_current_movement(mov_action_t action, direction_t direction) {
    if (action == STOP) {
        if (current_direction == direction)
            moving = false;
        else
            return;
    } else if (action == START) {
        current_direction = direction;
        moving = true;
    }
}