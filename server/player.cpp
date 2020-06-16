#include "player.h"

Player::Player(int entity_id, int head_id, int body_id, std::string name,
               Map &map)
    : Entity(id),
      head_id(head_id),
      body_id(body_id),
      name(name),
      map(map),
      move_accumulator(0) {}

void Player::update(unsigned int delta_t) {
    int time_between_tiles = 1000 / player_speed;
    move_accumulator += delta_t;

    if (move_accumulator > time_between_tiles) {
        int steps = move_accumulator /
                    time_between_tiles;  // Esto deberia dar 1 salvo que el
                                         // ciclo de juego se ponga MUY slow

        /* current_speed_x y current_speed_y no deberian ser nunca
        simultaneamente diferentes de 0. */
        int steps_x = current_speed_x * steps;
        int steps_y = current_speed_y * steps;
        map.move(this->id, {steps_x, steps_y});

        /* Se guarda el restante para la proxima actualizacion. */
        move_accumulator = move_accumulator % time_between_tiles;
    }
    // TODO: demas updates, como regeneraciones de vida/mana, etc.
}

entity_type_t Player::get_type() { return PLAYER; }

void Player::set_current_speed(int value_x, int value_y) {
    current_speed_x = value_x;
    current_speed_y = value_y;
}