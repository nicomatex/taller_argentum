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
      current_speed_x(0),
      current_speed_y(0) {
    visual_entity_info["type_id"] = get_type();
    visual_entity_info["head_id"] = head_id;
    visual_entity_info["body_id"] = body_id;
    visual_entity_info["name"] = name;
    visual_entity_info["helmet_id"] = helmet_id;
    visual_entity_info["armor_id"] = armor_id;
    visual_entity_info["shield_id"] = shield_id;
    visual_entity_info["weapon_id"] = weapon_id;
}

void Player::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / player_speed;
    move_accumulator += delta_t;

    if (move_accumulator >= time_between_tiles) {
        int steps = move_accumulator /
                    time_between_tiles;  // Esto deberia dar 1 salvo que el
                                         // ciclo de juego se ponga MUY slow

        /* current_speed_x y current_speed_y no deberian ser nunca
        simultaneamente diferentes de 0. */
        int steps_x = current_speed_x * steps;
        int steps_y = current_speed_y * steps;
        map.move(this->id, {steps_x, steps_y});

        /* Se guarda el restante para la proxima actualizacion. */
        if (steps_x != 0 || steps_y != 0) {
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

void Player::set_current_speed(int value_x, int value_y) {
    current_speed_x = value_x;
    current_speed_y = value_y;
}