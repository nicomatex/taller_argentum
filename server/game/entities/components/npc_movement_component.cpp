#include "npc_movement_component.h"

NpcMovementComponent::NpcMovementComponent(unsigned int movement_speed,
                                                   Map& map, EntityId entity_id)
    : MovementComponent(movement_speed),
      looking_direction(DOWN),
      map(map),
      entity_id(entity_id) {}
NpcMovementComponent::~NpcMovementComponent() {}

direction_t NpcMovementComponent::current_direction() const {
    return looking_direction;
}

position_t NpcMovementComponent::update(uint64_t delta_t) {
    return {0, 0};
}
