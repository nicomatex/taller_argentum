#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include "movement_component.h"

class PlayerMovementComponent : public MovementComponent {
   private:
    std::vector<direction_t> direction_history;
    bool moving;
    int move_accumulator;

   protected:
    direction_t current_direction() const override;

   public:
    PlayerMovementComponent(unsigned int ms);
    ~PlayerMovementComponent();

    void set_movement(mov_action_t action, direction_t direction);

    virtual position_t update(uint64_t delta_t) override;
};

#endif  // PLAYER_MOVEMENT_COMPONENT_H
