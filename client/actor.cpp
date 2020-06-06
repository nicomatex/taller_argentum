#include "actor.h"

#include <iostream>

#include "stdlib.h"
#include "visual_config.h"

Actor::Actor(AnimationPack &&animation_pack, int x, int y, int width,
             int height)
    : animation_pack(std::move(animation_pack)),
      VisualComponent(x, y, width, height),
      orientation(DOWN),
      movement_status(IDLE) {offset_timer.start();}

void Actor::_update_offset() {
    int delta_offset = (MOVEMENT_OFFSET * offset_timer.get_ticks());
    delta_offset /= MOVEMENT_TRANSITION_TIME;

    if (x_offset != 0) {
        int old_offset = x_offset;
        delta_offset *= x_offset < 0 ? 1 : -1;
        x_offset += delta_offset;
        if (x_offset * old_offset <= 0) { /* Si el movimiento ya termino. */
            x_offset = 0;
            offset_timer.stop();
        } else {
            offset_timer.start();
        }
    }
    if (y_offset != 0) {
        int old_offset = y_offset;
        delta_offset *= y_offset < 0 ? 1 : -1;
        y_offset += delta_offset;
        if (y_offset * old_offset <= 0) { /* Si el movimiento ya termino. */
            y_offset = 0;
            offset_timer.stop();
        } else {
            offset_timer.start();
        }
    }
}

void Actor::_update_status() {
    if (!offset_timer.is_started()) {
        movement_status = IDLE;
    }
}
void Actor::render(const SDLArea &dest) {
    animation_pack.render(orientation, movement_status, dest);
    _update_offset();
    _update_status();
}

void Actor::move(Orientation move_orientation, int steps) {
    movement_status = MOVING;
    orientation = move_orientation;

    switch (move_orientation) {
        case UP:
            y -= steps;
            y_offset = MOVEMENT_OFFSET * steps;
            break;
        case DOWN:
            y += steps;
            y_offset = -MOVEMENT_OFFSET * steps;
            break;
        case LEFT:
            x -= steps;
            x_offset = MOVEMENT_OFFSET * steps;
            break;
        case RIGHT:
            x += steps;
            x_offset = -MOVEMENT_OFFSET * steps;
            break;
    }
    offset_timer.start();
}

void Actor::set_move_status(MovementStatus new_movement_status) {
    movement_status = new_movement_status;
}

void Actor::set_orientation(Orientation new_orientation) {
    orientation = new_orientation;
}
