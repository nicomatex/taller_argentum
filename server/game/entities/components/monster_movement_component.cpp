#include "monster_movement_component.h"

#include <cstdlib>

#include "../../random_event_generator.h"

#define VIEW_RANGE 8

// Temp
#include <iostream>

direction_t get_direction_to_position(position_t from, position_t to) {
    position_t delta = {to.x - from.x, to.y - from.y};
    if (std::abs(delta.y) > std::abs(delta.x)) {
        if (delta.y > 0) {
            return DOWN;
        } else {
            return UP;
        }
    } else if (delta.x > 0) {
        return RIGHT;
    }
    return LEFT;
}

bool MonsterMovementComponent::update_direction() {
    position_t self_position = map.get_position(entity_id);
    position_t nearest_player =
        map.get_nearest_entity_pos(self_position, VIEW_RANGE, PLAYER);
    if (self_position.x == nearest_player.x &&
        self_position.y == nearest_player.y) {
        if (!RandomEventGenerator::random_in(0, 50)) {
            looking_direction =
                (direction_t)RandomEventGenerator::random_in(UP, RIGHT);
            return true;
        }
    } else {
        looking_direction =
            get_direction_to_position(self_position, nearest_player);
        return true;
    }
    return false;
}

direction_t MonsterMovementComponent::current_direction() const {
    return looking_direction;
}

MonsterMovementComponent::MonsterMovementComponent(unsigned int movement_speed,
                                                   Map& map, EntityId entity_id)
    : MovementComponent(movement_speed),
      entity_id(entity_id),
      map(map),
      looking_direction(DOWN),
      move_accumulator(0) {}
MonsterMovementComponent::~MonsterMovementComponent() {}

position_t MonsterMovementComponent::update(uint64_t delta_t) {
    int time_between_tiles = 1000 / movement_speed;
    move_accumulator += delta_t;

    position_t displacement = {0, 0};
    bool moving = false;
    if (move_accumulator >= time_between_tiles) {
        moving = update_direction();
        // Esto deberia dar 1 salvo que el
        // ciclo de juego se ponga MUY slow
        int distance = move_accumulator / time_between_tiles;

        if (moving) {
            displacement = get_displacement(displacement, distance);
        }

        /* Se guarda el restante para la proxima actualizacion. */
        if (moving && distance != 0) {
            move_accumulator = move_accumulator % time_between_tiles;
        } else {
            move_accumulator = time_between_tiles;
        }
    }
    return displacement;
}
