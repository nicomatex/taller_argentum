#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include "../../../../include/types.h"
#include "movement_component.h"

class PlayerMovementComponent : public MovementComponent {
   private:
    std::vector<direction_t> direction_history;
    int move_accumulator;
    bool moving;
    bool is_immobilized;
    int immobilized_counter;

   protected:
    direction_t current_direction() const override;

   public:
    PlayerMovementComponent(unsigned int ms);
    ~PlayerMovementComponent();

    void immobilize(int delta_t);

    void set_movement(mov_action_t action, direction_t direction);

    virtual position_t update(uint64_t delta_t) override;
};

#endif  // PLAYER_MOVEMENT_COMPONENT_H
