#include "visual_component.h"

#include <iostream>

#include "stdlib.h"
#include "visual_config.h"

VisualComponent::VisualComponent(AnimationPack &&animation_pack, int x_tile,
                                 int y_tile, int width_tile, int height_tile)
    : animation_pack(std::move(animation_pack)),
      x_tile(x_tile),
      y_tile(y_tile),
      width_tile(width_tile),
      height_tile(height_tile),
      orientation(DOWN),
      x_offset(0),
      y_offset(0) {
    timer.start();
}

void VisualComponent::_update_offset() {
    int delta_offset = (MOVEMENT_OFFSET * timer.get_ticks());
    delta_offset /= MOVEMENT_TRANSITION_TIME;
    
    if(x_offset != 0){
      int old_offset = x_offset;
      delta_offset *= x_offset < 0 ? 1 : -1;
      x_offset += delta_offset;
      if(x_offset * old_offset < 0) {
        x_offset = 0;
        timer.stop();
      }else{
        timer.start();
      }
    }
    if(y_offset != 0){
      int old_offset = y_offset;
      delta_offset *= y_offset < 0 ? 1 : -1;
      y_offset += delta_offset;
      if(y_offset * old_offset < 0) {
        y_offset = 0;
        timer.stop();
      }else{
        timer.start();
      }
    }
}

void VisualComponent::render(const SDLArea &dest) {
    animation_pack.render(orientation, movement_status, dest);
    _update_offset();
}

int VisualComponent::get_x_tile() const { return x_tile; }

int VisualComponent::get_y_tile() const { return y_tile; }

int VisualComponent::get_height_tile() const { return height_tile; }

int VisualComponent::get_width_tile() const { return width_tile; }

int VisualComponent::get_x_offset() { return x_offset; }

int VisualComponent::get_y_offset() { return y_offset; }

void VisualComponent::set_position(int new_x_tile, int new_y_tile) {
    if (new_x_tile < x_tile) {
        x_offset = MOVEMENT_OFFSET;
    } else if (new_x_tile > x_tile) {
        x_offset = -MOVEMENT_OFFSET;
    }

    if (new_y_tile < y_tile) {
        y_offset = MOVEMENT_OFFSET;
    } else if (new_y_tile > y_tile) {
        y_offset = -MOVEMENT_OFFSET;
    }
    timer.start();
    x_tile = new_x_tile;
    y_tile = new_y_tile;
}

void VisualComponent::set_move_status(MovementStatus new_movement_status) {
    movement_status = new_movement_status;
}

void VisualComponent::set_orientation(Orientation new_orientation) {
    orientation = new_orientation;
}