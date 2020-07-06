#include "player_movement_component.h"

PlayerMovementComponent::PlayerMovementComponent(unsigned int movement_speed)
    : MovementComponent(movement_speed), move_accumulator(0), moving(false) {}

PlayerMovementComponent::~PlayerMovementComponent() {}

direction_t PlayerMovementComponent::current_direction() const {
    if (direction_history.empty())
        return DOWN;
    return direction_history.back();
}

position_t PlayerMovementComponent::update(uint64_t delta_t) {
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

void PlayerMovementComponent::set_movement(mov_action_t action,
                                           direction_t direction) {
    if (action == STOP) {
        if (direction_history.empty())
            return;
        if (direction == direction_history.back()) {
            if (direction_history.size() == 1) {
                moving = false;
                return;
            }
            direction_history.pop_back();
        } else {
            auto pos = std::find(direction_history.begin(),
                                 direction_history.end(), direction);
            if (pos == direction_history.end())
                return;
            direction_history.erase(pos);
        }
    } else if (action == START) {
        if (direction_history.size() == 1 && moving == false) {
            direction_history.pop_back();
        }
        moving = true;
        direction_history.push_back(direction);
    }
}
