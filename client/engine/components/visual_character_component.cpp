#include "visual_character_component.h"

#include "../ECS/entity.h"
#include "../actor.h"
#include "../engine_config.h"
#include "../resource_manager.h"
#include "../visual_config.h"
#include "position_component.h"

VisualCharacterComponent::VisualCharacterComponent(int head_id, int body_id,
                                                   int weapon_id, int shield_id,
                                                   int helmet_id, int armor_id,
                                                   int speed)
    : speed(speed), initialized(false) {
    part_ids["body"] = body_id;
    part_ids["head"] = head_id;
    part_ids["armor"] = armor_id;
    part_ids["weapon"] = weapon_id;
    part_ids["shield"] = shield_id;
    part_ids["helmet"] = helmet_id;

    set_part("body", "bodies", body_id, BODY_CONFIG);
    set_part("head", "heads", head_id, HEAD_CONFIG);
    set_part("helmet", "helmets", helmet_id, HEAD_CONFIG);
    set_part("weapon", "weapons", weapon_id, WEAPON_CONFIG);
    set_part("shield", "shields", shield_id, BODY_CONFIG);
    set_part("armor", "armors", armor_id, BODY_CONFIG);
}

void VisualCharacterComponent::server_update(nlohmann::json update_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    set_part("body", "bodies", update_info["body_id"], BODY_CONFIG);
    set_part("head", "heads", update_info["head_id"], HEAD_CONFIG);
    set_part("helmet", "helmets", update_info["helmet_id"], HEAD_CONFIG);
    set_part("weapon", "weapons", update_info["weapon_id"], WEAPON_CONFIG);
    set_part("shield", "shields", update_info["shield_id"], BODY_CONFIG);
    set_part("armor", "armors", update_info["armor_id"], BODY_CONFIG);
    set_orientation(update_info["direction"]);
}

void VisualCharacterComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    int current_x = entity->get_component<PositionComponent>().get_x();
    int current_y = entity->get_component<PositionComponent>().get_y();
}

void VisualCharacterComponent::set_part(const std::string& type,
                                        const std::string& texture_family,
                                        int new_part_id,
                                        visual_info_t visual_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    try {
        if (parts.count(type) != 0) {
            if (part_ids.at(type) == new_part_id) {
                return;
            }
        }
        if (new_part_id != 0) {
            Actor new_part(ResourceManager::get_instance().get_animation_pack(
                               texture_family, new_part_id),
                           visual_info);
            if (parts.count(type) != 0) {
                new_part.set_move_status(parts.at(type).get_movement_status());
                new_part.set_orientation(parts.at(type).get_direction());
                parts.erase(type);
            }
            parts.insert(std::make_pair(type, new_part));
            part_ids[type] = new_part_id;
        } else {
            parts.erase(type);
            part_ids.erase(type);
        }
    } catch (std::exception& e) {
        std::cout << "Error actualizando " << type << std::endl;
        throw;
    }
}

void VisualCharacterComponent::draw(Camera& camera) {
    std::unique_lock<std::recursive_mutex> l(m);

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
    std::unique_lock<std::recursive_mutex> l(m);
    return parts.at(type);
}

VisualCharacterComponent::~VisualCharacterComponent() {}

void VisualCharacterComponent::bind_to_camera(Camera& bind_camera) {
    std::unique_lock<std::recursive_mutex> l(m);
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

void VisualCharacterComponent::set_orientation(direction_t new_orientation) {
    std::unique_lock<std::recursive_mutex> l(m);
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
    if (!(entity->get_component<PositionComponent>().position_initialized()))
        return;

    direction_t orientation;
    movement_status_t movement_status;

    if (abs(delta_x) > abs(delta_y)) {
        if (delta_x > 0) {
            orientation = RIGHT;
        } else {
            orientation = LEFT;
        }
    } else {
        if (delta_y > 0) {
            orientation = DOWN;
        } else {
            orientation = UP;
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
    std::unique_lock<std::recursive_mutex> l(m);
    /* Se actualiza la posicion de todos los actores para matchear con
    la componente de posicion. */
    int new_x = entity->get_component<PositionComponent>().get_x();
    int new_y = entity->get_component<PositionComponent>().get_y();
    if (initialized) {
        _update_animation(new_x - current_x, new_y - current_y);
        _update_offset();
    } else if (entity->get_component<PositionComponent>()
                   .position_initialized()) {
        initialized = true;
    }
    current_x = new_x;
    current_y = new_y;
    for (auto& part : parts) {
        part.second.update();
    }
}