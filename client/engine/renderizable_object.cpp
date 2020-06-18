#include "renderizable_object.h"

RenderizableObject::RenderizableObject(int width, int height,
                                       int x_offset, int y_offset)
    :
      width(width),
      height(height),
      x_offset(x_offset),
      y_offset(y_offset) {}

int RenderizableObject::get_height() const { return height; }

int RenderizableObject::get_width() const { return width; }

int RenderizableObject::get_x_offset() const { return x_offset; }

int RenderizableObject::get_y_offset() const { return y_offset; }

void RenderizableObject::update() {}