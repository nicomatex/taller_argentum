#include "visual_component.h"

VisualComponent::VisualComponent(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), x_offset(0), y_offset(0) {}

int VisualComponent::get_x() const { return x; }

int VisualComponent::get_y() const { return y; }

int VisualComponent::get_height() const { return height; }

int VisualComponent::get_width() const { return width; }

int VisualComponent::get_x_offset() const { return x_offset; }

int VisualComponent::get_y_offset() const { return y_offset; }

void VisualComponent::set_position(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}