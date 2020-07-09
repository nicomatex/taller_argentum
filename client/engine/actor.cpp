#include "actor.h"

#include <iostream>

#include "engine_config.h"
#include "stdlib.h"

Actor::Actor(AnimationPack& animation_pack, visual_info_t visual_info)
    : RenderizableObject(visual_info),
      animation_pack(animation_pack),
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

void Actor::update() { _update_status(); }

direction_t Actor::get_direction() { return orientation; }

movement_status_t Actor::get_movement_status() { return movement_status; }

Actor::Actor(const Actor& other)
    : RenderizableObject(other),
      animation_pack(other.animation_pack),
      orientation(other.orientation),
      movement_status(other.movement_status) {}

Actor& Actor::operator=(const Actor& other) {
    animation_pack = other.animation_pack;
    orientation = other.orientation;
    movement_status = other.movement_status;
    RenderizableObject::operator=(other);
    return *this;
}