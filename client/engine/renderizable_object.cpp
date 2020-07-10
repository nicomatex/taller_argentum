#include "renderizable_object.h"

RenderizableObject::RenderizableObject(visual_info_t visual_info)
    : visual_info(visual_info) {}

RenderizableObject::RenderizableObject(const RenderizableObject &other) {
    visual_info = other.visual_info;
}

RenderizableObject &RenderizableObject::operator=(
    const RenderizableObject &other) {
    visual_info = other.visual_info;
    return *this;
}

int RenderizableObject::get_height() const {
    return visual_info.height;
}

int RenderizableObject::get_width() const {
    return visual_info.width;
}

int RenderizableObject::get_x_offset() const {
    return visual_info.offset_x;
}

int RenderizableObject::get_y_offset() const {
    return visual_info.offset_y;
}

void RenderizableObject::set_visual_info(visual_info_t new_visual_info){
    visual_info = new_visual_info;
}

void RenderizableObject::set_offset(int new_x_offset, int new_y_offset){
    visual_info.offset_x = new_x_offset;
    visual_info.offset_y = new_y_offset;
}

void RenderizableObject::update() {}