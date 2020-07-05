#include "monster_movement_component.h"

#include "random_event_generator.h"

#define VIEW_RANGE 3

direction_t get_direction_to_position(position_t from, position_t to) {
    position_t delta = {{to.y - from.y}, {to.x - from.x}};
    if (delta.y > 0)
        return DOWN;
    else if (delta.y < 0)
        return UP;
    else if (delta.x > 0)
        return RIGHT;
    return LEFT;
}

void MonsterMovementComponent::update_direction() {
    position_t self_position = map.get_position(entity_id);
    position_t nearest_player =
        map.get_nearest_entity_pos(self_position, VIEW_RANGE, PLAYER);
    if (self_position.x == nearest_player.x &&
        self_position.y == nearest_player.y)
        looking_direction =
            (direction_t)RandomEventGenerator::random_in(UP, LEFT);
    else
        looking_direction =
            get_direction_to_position(self_position, nearest_player);
}

direction_t MonsterMovementComponent::current_direction() const {
    return looking_direction;
}

MonsterMovementComponent::MonsterMovementComponent(unsigned int movement_speed,
                                                   Map& map, EntityId entity_id)
    : MovementComponent(movement_speed),
      looking_direction(DOWN),
      map(map),
      entity_id(entity_id) {}
MonsterMovementComponent::~MonsterMovementComponent() {}

position_t MonsterMovementComponent::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / movement_speed;
    move_accumulator += delta_t;

    position_t displacement = {0, 0};

    update_direction();
    if (move_accumulator >= time_between_tiles) {
        // Esto deberia dar 1 salvo que el
        // ciclo de juego se ponga MUY slow
        int distance = move_accumulator / time_between_tiles;

        displacement = get_displacement(displacement, distance);
        move_accumulator = move_accumulator % time_between_tiles;
    }
    return displacement;
}
