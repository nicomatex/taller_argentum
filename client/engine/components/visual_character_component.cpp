#include "visual_character_component.h"

#include "../ECS/entity.h"
#include "../actor.h"
#include "../engine_config.h"
#include "../resource_manager.h"
#include "../visual_config.h"
#include "position_component.h"

VisualCharacterComponent::VisualCharacterComponent(int head_id, int body_id,
                                                   int weapon_id, int shield_id,
                                                   int helmet_id,int armor_id, int speed)
    : speed(speed),
      head_id(head_id),
      body_id(body_id),
      helmet_id(helmet_id),
      weapon_id(weapon_id),
      shield_id(shield_id),
      armor_id(armor_id) {
    if (head_id != 0) {
        Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                      head_id),
                   HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
        parts.insert(std::make_pair("head", head));
    }
    if (armor_id != 0) {
        Actor armor(ResourceManager::get_instance().get_animation_pack("armors",
                                                                      armor_id),
                   BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
        parts.insert(std::make_pair("body", armor));
    }else if (body_id != 0) {
        Actor body(ResourceManager::get_instance().get_animation_pack("bodies",
                                                                      body_id),
                   BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
        parts.insert(std::make_pair("body", body));
    }
    if (weapon_id != 0) {
        Actor weapon(ResourceManager::get_instance().get_animation_pack(
                         "weapons", weapon_id),
                     WEAPON_WIDTH, WEAPON_HEIGHT, WEAPON_OFFSET_X,
                     WEAPON_OFFSET_Y);
        parts.insert(std::make_pair("weapon", weapon));
    }
    if (shield_id != 0) {
        Actor shield(ResourceManager::get_instance().get_animation_pack(
                         "shields", shield_id),
                     SHIELD_WIDTH, SHIELD_HEIGHT, SHIELD_OFFSET_X,
                     SHIELD_OFFSET_Y);
        parts.insert(std::make_pair("shield", shield));
    }
    if (helmet_id != 0) {
        Actor helmet(ResourceManager::get_instance().get_animation_pack(
                         "helmets", helmet_id),
                     HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
        parts.insert(std::make_pair("helmet", helmet));
    }
}

void VisualCharacterComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    int current_x = entity->get_component<PositionComponent>().get_x();
    int current_y = entity->get_component<PositionComponent>().get_y();
}

void VisualCharacterComponent::set_head(int new_head_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_head_id == head_id) return;
    Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                  new_head_id),
               HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
    head.set_move_status(parts.at("head").get_movement_status());
    head.set_orientation(parts.at("head").get_direction());
    parts.erase("head");
    parts.insert(std::make_pair("head", head));
    head_id = new_head_id;
}

void VisualCharacterComponent::set_body(int new_body_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_body_id == body_id) return;
    Actor body(ResourceManager::get_instance().get_animation_pack("bodies",
                                                                  new_body_id),
               BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
    body.set_move_status(parts.at("body").get_movement_status());
    body.set_orientation(parts.at("body").get_direction());
    parts.erase("body");
    parts.insert(std::make_pair("body", body));
    body_id = new_body_id;
}

void VisualCharacterComponent::set_weapon(int new_weapon_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_weapon_id == weapon_id) return;
    Actor weapon(ResourceManager::get_instance().get_animation_pack(
                     "weapons", new_weapon_id),
                 WEAPON_WIDTH, WEAPON_HEIGHT, WEAPON_OFFSET_X, WEAPON_OFFSET_Y);
    weapon.set_move_status(parts.at("weapon").get_movement_status());
    weapon.set_orientation(parts.at("weapon").get_direction());
    parts.erase("weapon");
    parts.insert(std::make_pair("weapon", weapon));
    weapon_id = new_weapon_id;
}

void VisualCharacterComponent::set_helmet(int new_helmet_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_helmet_id == helmet_id) return;
    Actor helmet(ResourceManager::get_instance().get_animation_pack(
                     "helmets", new_helmet_id),
                 HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
    helmet.set_move_status(parts.at("helmet").get_movement_status());
    helmet.set_orientation(parts.at("helmet").get_direction());
    parts.erase("helmet");
    parts.insert(std::make_pair("helmet", helmet));
    helmet_id = new_helmet_id;
}

void VisualCharacterComponent::set_shield(int new_shield_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_shield_id == shield_id) return;
    Actor shield(ResourceManager::get_instance().get_animation_pack(
                     "shields", new_shield_id),
                 SHIELD_WIDTH, SHIELD_HEIGHT, SHIELD_OFFSET_X, SHIELD_OFFSET_Y);
    shield.set_move_status(parts.at("shield").get_movement_status());
    shield.set_orientation(parts.at("shield").get_direction());
    parts.erase("shield");
    parts.insert(std::make_pair("shield", shield));
    shield_id = new_shield_id;
}

void VisualCharacterComponent::set_armor(int new_armor_id) {
    std::unique_lock<std::mutex> l(m);
    if (new_armor_id == armor_id) return;
    Actor armor(ResourceManager::get_instance().get_animation_pack(
                     "armors", new_armor_id),
                 BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
    armor.set_move_status(parts.at("body").get_movement_status());
    armor.set_orientation(parts.at("body").get_direction());
    parts.erase("body");
    parts.insert(std::make_pair("body", armor));
    armor_id = new_armor_id;
}

void VisualCharacterComponent::draw(Camera& camera) {
    std::unique_lock<std::mutex> l(m);

    camera.draw(&parts.at("body"), current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&parts.at("head"), current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&parts.at("weapon"), current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&parts.at("shield"), current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&parts.at("helmet"), current_x, current_y, transition_offset_x,
                transition_offset_y);
    /*for (auto& it : parts) {
        camera.draw(&(it.second), current_x, current_y, transition_offset_x,
                    transition_offset_y);
    }*/
}

Actor& VisualCharacterComponent::get_part(const std::string& type) {
    std::unique_lock<std::mutex> l(m);
    return parts.at(type);
}

VisualCharacterComponent::~VisualCharacterComponent() {}

void VisualCharacterComponent::bind_to_camera(Camera& bind_camera) {
    std::unique_lock<std::mutex> l(m);
    camera = &bind_camera;
}

void VisualCharacterComponent::_update_offset() {
    int movement_transition_time = 1000 / speed;

    int delta_offset = (MOVEMENT_OFFSET * transition_timer.get_ticks());
    delta_offset /= movement_transition_time;

    bool stop_x = false;
    bool stop_y = false;

    float speed_factor_x =
        (float)abs(transition_offset_x) / (float)MOVEMENT_OFFSET;
    if (speed_factor_x < 1) speed_factor_x = 1;

    float speed_factor_y =
        (float)abs(transition_offset_y) / (float)MOVEMENT_OFFSET;
    if (speed_factor_y < 1) speed_factor_y = 1;

    if (transition_offset_x > 0) {
        transition_offset_x -= delta_offset * speed_factor_x;
        if (transition_offset_x <= 0) stop_x = true;
    } else if (transition_offset_x < 0) {
        transition_offset_x += delta_offset * speed_factor_x;
        if (transition_offset_x >= 0) stop_x = true;
    }
    if (transition_offset_y > 0) {
        transition_offset_y -= delta_offset * speed_factor_y;
        if (transition_offset_y <= 0) stop_y = true;
    } else if (transition_offset_y < 0) {
        transition_offset_y += delta_offset * speed_factor_y;
        if (transition_offset_y >= 0) stop_x = true;
    }

    if (stop_x || stop_y) {
        transition_timer.stop();
        if (stop_x) transition_offset_x = 0;
        if (stop_y) transition_offset_y = 0;
    } else {
        transition_timer.start();
    }
}

void VisualCharacterComponent::set_orientation(direction_t new_orientation){
    for (auto& part : parts) {
        part.second.set_orientation(new_orientation);
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
            // transition_offset_x = -MOVEMENT_OFFSET;
        } else {
            orientation = LEFT;
            // transition_offset_x = MOVEMENT_OFFSET;
        }
    } else {
        if (delta_y > 0) {
            orientation = DOWN;
            // transition_offset_y = -MOVEMENT_OFFSET;
        } else {
            orientation = UP;
            // transition_offset_y = MOVEMENT_OFFSET;
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
    std::unique_lock<std::mutex> l(m);
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