#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "../include/types.h"
#include "position.h"

class MovementComponent {
   private:
    unsigned int movement_speed;  // en tiles per second
    direction_t current_direction;
    bool moving;
    int move_accumulator;

   public:
    MovementComponent(unsigned int ms);
    ~MovementComponent();

    nlohmann::json get_data() const;

    void set_movement(mov_action_t action, direction_t direction);

    steps_t update(uint64_t delta_t);

    position_t get_facing_position(position_t position);
};

#endif  // MOVEMENT_COMPONENT_H
