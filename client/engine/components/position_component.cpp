#include "position_component.h"

#include <iostream>

#define speed 202

PositionComponent::PositionComponent() : x(0), y(0) {}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y){}

PositionComponent::~PositionComponent() {}

void PositionComponent::init() {}

void PositionComponent::update() {}

void PositionComponent::draw() {}

int PositionComponent::get_x() { return x; }

int PositionComponent::get_y() { return y; }

void PositionComponent::set_position(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}
