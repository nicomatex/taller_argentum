#include "renderizable_object.h"

RenderizableObject::RenderizableObject(int x, int y, int width, int height,
                                       int x_offset, int y_offset)
    : x(x),
      y(y),
      width(width),
      height(height),
      x_offset(x_offset),
      y_offset(y_offset) {}

int RenderizableObject::get_height() const { return height; }

int RenderizableObject::get_width() const { return width; }

int RenderizableObject::get_x_offset() const { return x_offset; }

int RenderizableObject::get_y_offset() const { return y_offset; }

int RenderizableObject::get_transition_offset_x() const { return 0; }

int RenderizableObject::get_transition_offset_y() const { return 0; }

int RenderizableObject::get_x() const { return x; }

int RenderizableObject::get_y() const { return y; }

void RenderizableObject::set_position(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

bool RenderizableObject::is_transitioning() const { return false; }

void RenderizableObject::update() {}