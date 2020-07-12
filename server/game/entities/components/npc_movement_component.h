#ifndef NPC_MOVEMENT_COMPONENT_H
#define NPC_MOVEMENT_COMPONENT_H

#include "../../../../include/types.h"
#include "../../map.h"
#include "movement_component.h"

class NpcMovementComponent : public MovementComponent {
   private:
    Map& map;
    EntityId entity_id;
    direction_t looking_direction;

   protected:
    direction_t current_direction() const override;

   public:
    NpcMovementComponent(unsigned int movement_speed, Map& map,
                         EntityId entity_id);
    ~NpcMovementComponent();

    position_t update(uint64_t delta_t) override;
};

#endif  // NPC_MOVEMENT_COMPONENT_H
