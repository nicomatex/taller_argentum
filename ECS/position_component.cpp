#include "position_component.h"
#include <iostream>

PositionComponent::PositionComponent() : x(0), y(0) {}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y) {}

PositionComponent::~PositionComponent() {}

void PositionComponent::init() {
}

void PositionComponent::update(int dt) {
	std::cout << "x: " << ++x << std::endl; // Aca deberia usarse el dt con la
	std::cout << "y: " << ++y << std::endl; // variable
}

void PositionComponent::draw() {}

int PositionComponent::get_x() {
	return x;
}

int PositionComponent::get_y() {
	return y;
}
