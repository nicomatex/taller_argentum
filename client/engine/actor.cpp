#include "actor.h"

#include <iostream>

#include "engine_config.h"
#include "stdlib.h"

Actor::Actor(AnimationPack& animation_pack, int width, int height, int x_offset,
             int y_offset)
    : animation_pack(animation_pack),
      RenderizableObject(width, height, x_offset, y_offset),
      orientation(DOWN),
      movement_status(IDLE),
      is_empty(false) {}

void Actor::_update_status() {}
void Actor::render(SDL_Rect dest) {
    animation_pack.render(orientation, movement_status, dest);
}

void Actor::set_move_status(movement_status_t new_movement_status) {
    movement_status = new_movement_status;
}

void Actor::set_orientation(direction_t new_direction) {
    orientation = new_direction;
}

int Actor::get_x_offset() const { return x_offset; }

int Actor::get_y_offset() const { return y_offset; }

void Actor::update() { _update_status(); }

direction_t Actor::get_direction() { return orientation; }

movement_status_t Actor::get_movement_status() { return movement_status; }

Actor::Actor(const Actor& other)
    : animation_pack(other.animation_pack),
      orientation(other.orientation),
      movement_status(other.movement_status),
      RenderizableObject(other) {}

Actor& Actor::operator=(const Actor& other){
    animation_pack = other.animation_pack;
    orientation = other.orientation;
    movement_status = other.movement_status;
    RenderizableObject::operator=(other);
    return *this;
}