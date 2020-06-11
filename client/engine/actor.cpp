#include "actor.h"

#include <iostream>

#include "stdlib.h"
#include "engine_config.h"

Actor::Actor(AnimationPack &animation_pack, int x, int y, int width, int height,
             int x_offset, int y_offset)
    : animation_pack(animation_pack),
      RenderizableObject(x, y, width, height, x_offset, y_offset),
      orientation(DOWN),
      movement_status(IDLE),
      transition_offset_x(0),
      transition_offset_y(0),
      is_empty(false) {}

void Actor::_update_offset() {
    int delta_offset = (MOVEMENT_OFFSET * transition_timer.get_ticks());
    delta_offset /= MOVEMENT_TRANSITION_TIME;

    if (transition_offset_x != 0) {
        int old_offset = transition_offset_x;
        delta_offset *= transition_offset_x < 0 ? 1 : -1;
        transition_offset_x += delta_offset;
        if (transition_offset_x * old_offset <=
            0) { /* Si el movimiento ya termino. */
            transition_offset_x = 0;
            transition_timer.stop();
        } else {
            transition_timer.start();
        }
    }
    if (transition_offset_y != 0) {
        int old_offset = transition_offset_y;
        delta_offset *= transition_offset_y < 0 ? 1 : -1;
        transition_offset_y += delta_offset;
        if (transition_offset_y * old_offset <=
            0) { /* Si el movimiento ya termino. */
            transition_offset_y = 0;
            transition_timer.stop();
        } else {
            transition_timer.start();
        }
    }
}

void Actor::_update_status() {
    if (!transition_timer.is_started()) {
        movement_status = IDLE;
    }
}
void Actor::render(const SDLArea &dest) {
    animation_pack.render(orientation, movement_status, dest);
}

void Actor::set_position(int new_x, int new_y, bool animation) {
    int delta_x = new_x - x;
    int delta_y = new_y - y;
    if (delta_x == 0 && delta_y == 0) return;

    x = new_x;
    y = new_y;

    if (animation) {
        if (abs(delta_x) > abs(delta_y)) {
            if (delta_x > 0) {
                orientation = RIGHT;
                transition_offset_x = -MOVEMENT_OFFSET;
            } else {
                orientation = LEFT;
                transition_offset_x = MOVEMENT_OFFSET;
            }
        } else {
            if (delta_y > 0) {
                orientation = DOWN;
                transition_offset_y = -MOVEMENT_OFFSET;
            } else {
                orientation = UP;
                transition_offset_y = MOVEMENT_OFFSET;
            }
        }
        movement_status = MOVING;
        transition_timer.start();
    }
}

void Actor::set_move_status(MovementStatus new_movement_status) {
    movement_status = new_movement_status;
}

void Actor::set_orientation(Orientation new_orientation) {
    orientation = new_orientation;
}

int Actor::get_x_offset() const { return transition_offset_x + x_offset; }

int Actor::get_y_offset() const { return transition_offset_y + y_offset; }

int Actor::get_transition_offset_x() const { return transition_offset_x; }

int Actor::get_transition_offset_y() const { return transition_offset_y; }

bool Actor::is_transitioning() const { return transition_timer.is_started(); }

void Actor::update() {
    _update_offset();
    _update_status();
}