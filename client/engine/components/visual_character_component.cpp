#include "visual_character_component.h"

#include "../ECS/entity.h"
#include "../actor.h"
#include "../engine_config.h"
#include "../resource_manager.h"
#include "../visual_config.h"
#include "position_component.h"
#include "stats_component.h"

VisualCharacterComponent::VisualCharacterComponent(int head_id, int body_id,
                                                   int weapon_id, int shield_id,
                                                   int helmet_id, int armor_id,
                                                   int speed,
                                                   const std::string& name)
    : speed(speed),
      initialized(false),
      transition_offset_x(0),
      transition_offset_y(0),
      render_name(name, NAME_COLOR, NAME_FONT_ID, NAME_INFO),
      render_damage("0", DAMAGE_COLOR, DAMAGE_FONT_ID, DAMAGE_INFO),
      health_bar(HEALTH_BAR_INFO),
      meditation_effect(ResourceManager::get_instance().get_sprite(
                            "meditations", MEDITATION_ID),
                        MEDITATION_CONFIG),
      recently_damaged(false),
      is_meditating(false) {
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
    is_meditating = update_info["is_meditating"];
}

void VisualCharacterComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    current_x = entity->get_component<PositionComponent>().get_x();
    current_y = entity->get_component<PositionComponent>().get_y();
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
            if (parts.count(type) != 0) {
                parts.erase(type);
                part_ids[type] = 0;
            }
        }
    } catch (std::exception& e) {
        std::cout << "Error actualizando " << type << std::endl;
        throw;
    }
}

void VisualCharacterComponent::draw(Camera& camera) {
    std::unique_lock<std::recursive_mutex> l(m);

    _draw_if_present(camera, "armor");
    if (part_ids.at("armor") == 0)
        _draw_if_present(camera, "body");
    _draw_if_present(camera, "head");
    _draw_if_present(camera, "weapon");
    _draw_if_present(camera, "shield");
    _draw_if_present(camera, "helmet");
    if (is_meditating) {
        camera.draw(&meditation_effect, current_x, current_y,
                    transition_offset_x, transition_offset_y);
    }
    if (recently_damaged) {
        camera.draw(&render_damage, current_x, current_y, transition_offset_x,
                    transition_offset_y);
    }

    camera.draw(&render_name, current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&health_bar, current_x, current_y, transition_offset_x,
                transition_offset_y);
}

void VisualCharacterComponent::_draw_if_present(Camera& camera,
                                                const std::string& part_name) {
    if (part_ids.at(part_name) == 0)
        return;
    camera.draw(&parts.at(part_name), current_x, current_y, transition_offset_x,
                transition_offset_y);
}

Actor& VisualCharacterComponent::get_part(const std::string& type) {
    std::unique_lock<std::recursive_mutex> l(m);
    return parts.at(type);
}

VisualCharacterComponent::~VisualCharacterComponent() {}

void VisualCharacterComponent::_update_offset() {
    int movement_transition_time = 1000 / speed;

    int delta_offset = (MOVEMENT_OFFSET * transition_timer.get_ticks());
    delta_offset /= movement_transition_time;

    bool stop_x = false;
    bool stop_y = false;

    float speed_factor_x =
        (float)abs(transition_offset_x) / (float)MOVEMENT_OFFSET;
    if (speed_factor_x < 1)
        speed_factor_x = 1;

    float speed_factor_y =
        (float)abs(transition_offset_y) / (float)MOVEMENT_OFFSET;
    if (speed_factor_y < 1)
        speed_factor_y = 1;

    if (transition_offset_x > 0) {
        transition_offset_x -= delta_offset * speed_factor_x;
        if (transition_offset_x <= 0)
            stop_x = true;
    } else if (transition_offset_x < 0) {
        transition_offset_x += delta_offset * speed_factor_x;
        if (transition_offset_x >= 0)
            stop_x = true;
    } else if (transition_offset_y > 0) {
        transition_offset_y -= delta_offset * speed_factor_y;
        if (transition_offset_y <= 0)
            stop_y = true;
    } else if (transition_offset_y < 0) {
        transition_offset_y += delta_offset * speed_factor_y;
        if (transition_offset_y >= 0)
            stop_x = true;
    }

    if (stop_x || stop_y) {
        transition_timer.stop();
        if (stop_x)
            transition_offset_x = 0;
        if (stop_y)
            transition_offset_y = 0;
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

    if (delta_x == 0 && delta_y == 0)
        return;
    if (!(entity->get_component<PositionComponent>().position_initialized()))
        return;

    movement_status_t movement_status;

    transition_offset_x -= delta_x * MOVEMENT_OFFSET;
    transition_offset_y -= delta_y * MOVEMENT_OFFSET;

    movement_status = MOVING;
    for (auto& part : parts) {
        part.second.set_move_status(movement_status);
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
    if (recently_damaged) {
        if (damage_render_timer.get_ticks() >= DAMAGE_TEXT_DURATION) {
            recently_damaged = false;
            damage_render_timer.stop();
        }
    }
    StatsComponent& stats = entity->get_component<StatsComponent>();
    health_bar.set_fill_proportion((float)stats.get_stat_current_value("hp") /
                                   (float)stats.get_stat_max_value("hp"));
}

bool VisualCharacterComponent::is_moving() {
    return transition_offset_x != 0 || transition_offset_y != 0;
}

int VisualCharacterComponent::get_part_id(const std::string& part_name) {
    std::unique_lock<std::recursive_mutex> l(m);
    return part_ids.at(part_name);
}

void VisualCharacterComponent::display_damage(int damage) {
    render_damage.update_text("-" + std::to_string(damage));
    recently_damaged = true;
    damage_render_timer.start();
}