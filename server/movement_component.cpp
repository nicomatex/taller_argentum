#include "movement_component.h"

#include <algorithm>

// Temp
#include <iostream>

MovementComponent::MovementComponent(unsigned int movement_speed)
    : movement_speed(movement_speed), move_accumulator(0), moving(false) {}

MovementComponent::~MovementComponent() {}

direction_t MovementComponent::current_direction() const {
    if (direction_history.empty())
        return DOWN;
    return direction_history.back();
}

nlohmann::json MovementComponent::get_data() const {
    return {{"direction", current_direction()}};
}

position_t MovementComponent::get_displacement(position_t pos, int dist) const {
    switch (current_direction()) {
        case UP:
            pos = {pos.x, pos.y - dist};
            break;
        case DOWN:
            pos = {pos.x, pos.y + dist};
            break;
        case RIGHT:
            pos = {pos.x + dist, pos.y};
            break;
        case LEFT:
            pos = {pos.x - dist, pos.y};
            break;
    }
    return pos;
}

position_t MovementComponent::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / movement_speed;
    move_accumulator += delta_t;

    position_t steps = {0, 0};

    if (move_accumulator >= time_between_tiles) {
        // Esto deberia dar 1 salvo que el
        // ciclo de juego se ponga MUY slow
        int distance = move_accumulator / time_between_tiles;

        if (moving) {
            steps = get_displacement(steps, distance);
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
    return get_displacement(position, 1);
}

void MovementComponent::set_movement(mov_action_t action,
                                     direction_t direction) {
    std::cerr << std::endl;
    if (action == STOP) {
        if (direction == direction_history.back()) {
            if (direction_history.size() == 1) {
                moving = false;
                return;
            }
            direction_history.pop_back();
        } else {
            direction_history.erase(std::find(
                direction_history.begin(), direction_history.end(), direction));
        }
    } else if (action == START) {
        if (direction_history.size() == 1 && moving == false) {
            direction_history.pop_back();
        }
        moving = true;
        direction_history.push_back(direction);
    }
}
