#include "movement_component.h"

// Temp
#include <iostream>

MovementComponent::MovementComponent(unsigned int movement_speed)
    : movement_speed(movement_speed) {}

MovementComponent::~MovementComponent() {}

nlohmann::json MovementComponent::get_data() const {
    return {{"direction", current_direction()}, {"move_speed", movement_speed}};
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

position_t MovementComponent::get_facing_position(position_t position) {
    return get_displacement(position, 1);
}
