#include "actor.h"

#include <iostream>

#include "stdlib.h"
#include "visual_config.h"

Actor::Actor(AnimationPack &animation_pack, int x, int y, int width,
             int height, int x_offset, int y_offset)
    : animation_pack(animation_pack),
      VisualComponent(x, y, width, height,x_offset,y_offset),
      orientation(DOWN),
      movement_status(IDLE),
      transition_offset_x(0),
      transition_offset_y(0) {}

void Actor::_update_offset() {
    int delta_offset = (MOVEMENT_OFFSET * offset_timer.get_ticks());
    delta_offset /= MOVEMENT_TRANSITION_TIME;

    if (transition_offset_x != 0) {
        int old_offset = transition_offset_x;
        delta_offset *= transition_offset_x < 0 ? 1 : -1;
        transition_offset_x += delta_offset;
        if (transition_offset_x * old_offset <= 0) { /* Si el movimiento ya termino. */
            transition_offset_x = 0;
            offset_timer.stop();
        } else {
            offset_timer.start();
        }
    }
    if (transition_offset_y != 0) {
        int old_offset = transition_offset_y;
        delta_offset *= transition_offset_y < 0 ? 1 : -1;
        transition_offset_y += delta_offset;
        if (transition_offset_y * old_offset <= 0) { /* Si el movimiento ya termino. */
            transition_offset_y = 0;
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
}

void Actor::move(Orientation move_orientation, int steps) {
    movement_status = MOVING;
    orientation = move_orientation;
    if(offset_timer.is_started()) return;
    switch (move_orientation) {
        case UP:
            y -= steps;
            transition_offset_y = MOVEMENT_OFFSET * steps;
            break;
        case DOWN:
            y += steps;
            transition_offset_y = -MOVEMENT_OFFSET * steps;
            break;
        case LEFT:
            x -= steps;
            transition_offset_x = MOVEMENT_OFFSET * steps;
            break;
        case RIGHT:
            x += steps;
            transition_offset_x = -MOVEMENT_OFFSET * steps;
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


int Actor::get_x_offset() const{
    return transition_offset_x + x_offset;
}

int Actor::get_y_offset() const{
    return transition_offset_y + y_offset;
}

bool Actor::is_transitioning() const{
    return offset_timer.is_started();
}

void Actor::update(){
    _update_offset();
    _update_status();
}