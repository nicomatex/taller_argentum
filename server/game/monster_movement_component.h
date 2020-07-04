#ifndef MONSTER_MOVEMENT_COMPONENT_H
#define MONSTER_MOVEMENT_COMPONENT_H

#include "../../include/types.h"
#include "map.h"
#include "movement_component.h"

class MonsterMovementComponent : public MovementComponent {
   private:
    Map& map;
    int move_accumulator;
    direction_t looking_direction;

   protected:
    direction_t current_direction() const override;

   public:
    MonsterMovementComponent(unsigned int movement_speed, Map& map);
    ~MonsterMovementComponent();

    position_t update(uint64_t delta_t) override;
};

#endif  // MONSTER_MOVEMENT_COMPONENT_H
