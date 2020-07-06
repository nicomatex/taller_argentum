#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <vector>

#include "../../../../include/types.h"
#include "../../position.h"

class MovementComponent {
   protected:
    unsigned int movement_speed;

    virtual direction_t current_direction() const = 0;
    position_t get_displacement(position_t pos, int dis) const;

   public:
    MovementComponent(unsigned int movement_speed);
    virtual ~MovementComponent();

    virtual nlohmann::json get_data() const;

    virtual position_t update(uint64_t delta_t) = 0;

    position_t get_facing_position(position_t position);
};

#endif  // MOVEMENT_COMPONENT_H
