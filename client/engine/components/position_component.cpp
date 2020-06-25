#include "position_component.h"

#include <iostream>

#define speed 202

PositionComponent::PositionComponent() : x(0), y(0),initialized(false) {}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y),initialized(false) {}

PositionComponent::~PositionComponent() {}

void PositionComponent::init() {}

void PositionComponent::update() {}

int PositionComponent::get_x(){
    std::unique_lock<std::mutex> l(m);
    return x;
}

int PositionComponent::get_y(){
    std::unique_lock<std::mutex> l(m);
    return y;
}

void PositionComponent::set_position(int new_x, int new_y) {
    std::unique_lock<std::mutex> l(m);
    x = new_x;
    y = new_y;
    if(!initialized){
        initialized = true;
    }
}


bool PositionComponent::position_initialized(){
    std::unique_lock<std::mutex> l(m);
    return initialized;
}