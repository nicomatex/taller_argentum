#include "movement_component.h"

// Temp
#include <iostream>

MovementComponent::MovementComponent(unsigned int movement_speed)
    : movement_speed(movement_speed),
      move_accumulator(0),
      moving(false),
      current_direction(DOWN) {}

MovementComponent::~MovementComponent() {}

nlohmann::json MovementComponent::get_data() const {
    return {{"direction", current_direction}};
}

steps_t MovementComponent::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / movement_speed;
    move_accumulator += delta_t;

    steps_t steps = {0, 0};

    if (move_accumulator >= time_between_tiles) {
        // Esto deberia dar 1 salvo que el
        // ciclo de juego se ponga MUY slow
        int distance = move_accumulator / time_between_tiles;

        if (moving) {
            switch (current_direction) {
                case UP:
                    steps = {0, -distance};
                    break;
                case DOWN:
                    steps = {0, distance};
                    break;
                case RIGHT:
                    steps = {distance, 0};
                    break;
                case LEFT:
                    steps = {-distance, 0};
                    break;
            }
        }

        /* Se guarda el restante para la proxima actualizacion. */
        if (moving && distance != 0) {
            move_accumulator = move_accumulator % time_between_tiles;
        } else {
            move_accumulator = time_between_tiles;
        }
    }
    return steps;
}

position_t MovementComponent::get_facing_position(position_t position) {
    position_t facing_pos;
    switch (current_direction) {
        case UP:
            facing_pos = {position.x, position.y - 1};
            break;
        case DOWN:
            facing_pos = {position.x, position.y + 1};
            break;
        case RIGHT:
            facing_pos = {position.x + 1, position.y};
            break;
        case LEFT:
            facing_pos = {position.x - 1, position.y};
            break;
    }
    return facing_pos;
}

void MovementComponent::set_movement(mov_action_t action,
                                     direction_t direction) {
    if (action == STOP && current_direction == direction) {
        moving = false;
    } else if (action == START) {
        current_direction = direction;
        moving = true;
    }
}
