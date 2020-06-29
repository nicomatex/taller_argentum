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

void RenderizableObject::update() {}