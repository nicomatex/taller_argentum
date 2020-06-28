#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <vector>

#include "../include/types.h"
#include "position.h"

class MovementComponent {
   private:
    unsigned int movement_speed;  // en tiles per second
    std::vector<direction_t> direction_history;
    bool moving;
    int move_accumulator;

    direction_t current_direction() const;
    position_t get_displacement(position_t pos, int dis) const;

   public:
    MovementComponent(unsigned int ms);
    ~MovementComponent();

    nlohmann::json get_data() const;

    void set_movement(mov_action_t action, direction_t direction);

    position_t update(uint64_t delta_t);

    position_t get_facing_position(position_t position);
};

#endif  // MOVEMENT_COMPONENT_H
