#include "visual_character_component.h"

#include "../ECS/entity.h"
#include "../actor.h"
#include "../engine_config.h"
#include "../resource_manager.h"
#include "../visual_config.h"
#include "position_component.h"

VisualCharacterComponent::VisualCharacterComponent(int head_id, int body_id,
                                                   int weapon_id,
                                                   int offhand_id,int speed):speed(speed) {
    if (head_id != 0) {
        Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                      head_id),
                   HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
        parts.insert(std::make_pair("head", head));
    }
    if (body_id != 0) {
        Actor body(ResourceManager::get_instance().get_animation_pack("bodies",
                                                                      body_id),
                   BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
        parts.insert(std::make_pair("body", body));
    }
}

void VisualCharacterComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    int current_x = entity->get_component<PositionComponent>().get_x();
    int current_y = entity->get_component<PositionComponent>().get_y();
}

void VisualCharacterComponent::set_head(int new_head_id) {
    Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                  new_head_id),
               HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
    parts.erase("head");
    parts.insert(std::make_pair("head", head));
}

void VisualCharacterComponent::set_body(int new_body_id) {
    Actor body(ResourceManager::get_instance().get_animation_pack("bodies",
                                                                  new_body_id),
               BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
    parts.erase("body");
    parts.insert(std::make_pair("body", body));
}

void VisualCharacterComponent::draw(Camera &camera) {
    for (auto& it : parts) {
        camera.draw(&(it.second), current_x, current_y, transition_offset_x,
                     transition_offset_y);
    }
}

Actor& VisualCharacterComponent::get_part(const std::string& type) {
    return parts.at(type);
}

VisualCharacterComponent::~VisualCharacterComponent() {}

void VisualCharacterComponent::bind_to_camera(Camera& bind_camera) {
    camera = &bind_camera;
}

void VisualCharacterComponent::_update_offset() {
    int movement_transition_time = 1000 / speed;

    int delta_offset = (MOVEMENT_OFFSET * transition_timer.get_ticks());
    delta_offset /= movement_transition_time;

    bool stop_x = false;
    bool stop_y = false;

    float speed_factor_x = (float)abs(transition_offset_x) / (float)MOVEMENT_OFFSET;
    if(speed_factor_x < 1) speed_factor_x = 1;

    float speed_factor_y = (float)abs(transition_offset_y) / (float)MOVEMENT_OFFSET;
    if(speed_factor_y < 1) speed_factor_y = 1;
    
    if(transition_offset_x > 0){
        transition_offset_x -= delta_offset * speed_factor_x;
        if(transition_offset_x <= 0) stop_x = true;
    }else if(transition_offset_x < 0){
        transition_offset_x += delta_offset * speed_factor_x;
        if(transition_offset_x >= 0) stop_x = true;
    }
    if(transition_offset_y > 0){
        transition_offset_y -= delta_offset * speed_factor_y;
        if(transition_offset_y <= 0) stop_y = true;
    }else if(transition_offset_y < 0){
        transition_offset_y += delta_offset * speed_factor_y;
        if(transition_offset_y >= 0) stop_x = true;
    }

    if(stop_x || stop_y){
        transition_timer.stop();
        if(stop_x) transition_offset_x = 0;
        if(stop_y) transition_offset_y = 0;
    }else{
        transition_timer.start();
    }

}

void VisualCharacterComponent::_update_animation(int delta_x, int delta_y) {
    if (!transition_timer.is_started()) {
        for (auto& part : parts) {
            part.second.set_move_status(IDLE);
        }
    }

    if (delta_x == 0 && delta_y == 0) return;
    direction_t orientation;
    movement_status_t movement_status;

    if (abs(delta_x) > abs(delta_y)) {
        if (delta_x > 0) {
            orientation = RIGHT;
            //transition_offset_x = -MOVEMENT_OFFSET;
        } else {
            orientation = LEFT;
            //transition_offset_x = MOVEMENT_OFFSET;
        }
    } else {
        if (delta_y > 0) {
            orientation = DOWN;
            //transition_offset_y = -MOVEMENT_OFFSET;
        } else {
            orientation = UP;
            //transition_offset_y = MOVEMENT_OFFSET;
        }
    }

    transition_offset_x -= delta_x * MOVEMENT_OFFSET;
    transition_offset_y -= delta_y * MOVEMENT_OFFSET;

    movement_status = MOVING;
    for (auto& part : parts) {
        part.second.set_move_status(movement_status);
        part.second.set_orientation(orientation);
    }
    transition_timer.start();
}

void VisualCharacterComponent::update() {
    /* Se actualiza la posicion de todos los actores para matchear con
    la componente de posicion. */
    int new_x = entity->get_component<PositionComponent>().get_x();
    int new_y = entity->get_component<PositionComponent>().get_y();
    _update_animation(new_x - current_x, new_y - current_y);
    _update_offset();
    current_x = new_x;
    current_y = new_y;
    for (auto& part : parts) {
        part.second.update();
    }
}