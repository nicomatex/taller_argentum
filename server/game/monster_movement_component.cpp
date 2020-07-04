#include "monster_movement_component.h"

direction_t MonsterMovementComponent::current_direction() const {
    return looking_direction;
}

MonsterMovementComponent::MonsterMovementComponent(unsigned int movement_speed,
                                                   Map& map)
    : MovementComponent(movement_speed), looking_direction(DOWN), map(map) {}
MonsterMovementComponent::~MonsterMovementComponent() {}

position_t MonsterMovementComponent::update(uint64_t delta_t) {
    return {0, 0};
}
